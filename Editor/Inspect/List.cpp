#include "Precompile.h"
#include "List.h"

#include "Foundation/String/Tokenize.h"

using namespace Helium;
using namespace Helium::Editor;

BEGIN_EVENT_TABLE(ListWindow, wxListBox)
END_EVENT_TABLE();

ListWidget::ListWidget( Inspect::List* control )
: Widget( control )
, m_ListControl( control )
, m_ListWindow( NULL )
{

}

void ListWidget::Create(wxWindow* parent)
{
    HELIUM_ASSERT( !m_ListWindow );

    // allocate window and connect common listeners
    SetWindow( m_ListWindow = new ListWindow( parent, this, ( m_ListControl->a_IsSorted.Get() ? wxLB_SORT : 0 ) | wxLB_SINGLE | wxLB_HSCROLL) );

    // add listeners

    // layout metrics
    wxSize size( -1, m_ListControl->GetCanvas()->GetStdSize(Math::SingleAxes::Y) * 5 );
    m_Window->SetSize( size );
    m_Window->SetMinSize( size );
    m_Window->SetMaxSize( size );

    // update state of attributes that are not refreshed during Read()
}

void ListWidget::Destroy()
{
    HELIUM_ASSERT( m_ListWindow );

    SetWindow( NULL );

    // remove listeners

    m_ListWindow->Destroy();
    m_ListWindow = NULL;
}

void ListWidget::Read()
{
    // from data into ui
    HELIUM_ASSERT( m_ListControl->IsBound() );

    tstring str;
    m_ListControl->ReadStringData( str );

    tstring delimiter;
    bool converted = Helium::ConvertString( Reflect::s_ContainerItemDelimiter, delimiter );
    HELIUM_ASSERT( converted );

    std::vector< tstring > items;
    Helium::Tokenize( str, items, delimiter );

    m_ListWindow->Freeze();
    m_ListWindow->Clear();
    std::vector< tstring >::const_iterator itr = items.begin();
    std::vector< tstring >::const_iterator end = items.end();
    for ( ; itr != end; ++itr )
    {
        m_ListWindow->Append( (*itr).c_str() );
    }
    m_ListWindow->Thaw();
}

bool ListWidget::Write()
{
    HELIUM_ASSERT( m_ListControl->IsBound() );

    tstring delimited, delimiter;
    bool converted = Helium::ConvertString( Reflect::s_ContainerItemDelimiter, delimiter );
    HELIUM_ASSERT( converted );

    const i32 total = m_ListWindow->GetCount();
    for ( i32 index = 0; index < total; ++index )
    {
        if ( !delimited.empty() )
        {
            delimited += delimiter;
        }

        const tstring val = m_ListWindow->GetString( index ).c_str();
        delimited += val;
    }

    return m_ListControl->WriteStringData( delimited );
}
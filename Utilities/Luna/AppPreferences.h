#pragma once

#include "API.h"
#include "Editor/Preferences.h"

namespace Luna
{
  class AppPreferences;

  AppPreferences* GetAppPreferences();

  class AppPreferences : public Preferences
  {
  private:
    bool m_UseTracker;

    // RTTI
  public:
    static void InitializeType();
    static void CleanupType();
    REFLECT_DECLARE_CLASS( AppPreferences, Preferences )
    static void EnumerateClass( Reflect::Compositor< AppPreferences >& comp );

  public:
    AppPreferences();

    virtual const std::string& GetCurrentVersion() const NOC_OVERRIDE;
    virtual std::string GetPreferencesPath() const NOC_OVERRIDE;

    const Reflect::Field* UseTrackerField() const;

  public:
      void UseTracker( bool useTracker );
      bool UseTracker() const
      {
          return m_UseTracker;
      }
    
  };
  typedef Nocturnal::SmartPtr< AppPreferences > AppPreferencesPtr;
}
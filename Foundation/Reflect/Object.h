#pragma once

#include "Platform/Types.h"
#include "Platform/Assert.h"
#include "Platform/Utility.h"

#include "Foundation/Automation/Event.h"
#include "Foundation/Automation/Attribute.h"
#include "Foundation/Container/ConcurrentHashSet.h"
#include "Foundation/File/Path.h"
#include "Foundation/Memory/ReferenceCounting.h"
#include "Foundation/Reflect/API.h"
#include "Foundation/Reflect/Exceptions.h"

namespace Helium
{
    namespace Reflect
    {
        class Object;
        class Type;
        class Composite;
        class Class;

        //
        // Reflect::ObjectRefCountSupport provides the support interface for managing reference counting data for
        // Reflect::Object instances.
        //

        class FOUNDATION_API ObjectRefCountSupport
        {
        public:
            /// Base type of reference counted object.
            typedef Object BaseType;

            /// @name Object Destruction Support
            //@{
            inline static void PreDestroy( Object* pObject );
            inline static void Destroy( Object* pObject );
            //@}

            /// @name Reference Count Proxy Allocation Interface
            //@{
            static RefCountProxy< Object >* Allocate();
            static void Release( RefCountProxy< Object >* pProxy );

            static void Shutdown();
            //@}

#if HELIUM_ENABLE_MEMORY_TRACKING
            /// @name Active Proxy Iteration
            //@{
            static size_t GetActiveProxyCount();
            static bool GetFirstActiveProxy(
                ConcurrentHashSet< RefCountProxy< Object >* >::ConstAccessor& rAccessor );
            //@}
#endif

        private:
            struct StaticData;

            /// Static proxy management data.
            static StaticData* sm_pStaticData;
        };


        //
        // Reflect::Object is a reference counted and type checked abstract base class
        //

        class Field;
        class Class;
        class Structure;

        //
        // Event delegate to support getting notified if this object changes
        //

        struct ObjectChangeArgs
        {
            const Object* m_Object;
            const Field* m_Field;

            ObjectChangeArgs( const Object* object, const Field* field = NULL )
                : m_Object( object )
                , m_Field( field )
            {
            }
        };
        typedef Helium::Signature< const ObjectChangeArgs&, Helium::AtomicRefCountBase > ObjectChangeSignature;


        //
        // Reflect::Object is the abstract base class of a serializable unit
        //
        class FOUNDATION_API Object HELIUM_ABSTRACT : NonCopyable
        {
        protected:
            HELIUM_DECLARE_REF_COUNT( Object, ObjectRefCountSupport );

        protected:
            Object();

        public:
            virtual ~Object();

            //
            // Memory
            //

            void* operator new( size_t bytes );
            void* operator new( size_t bytes, void* memory );
            void operator delete( void* ptr, size_t bytes );
            void operator delete( void* ptr, void* memory );

            virtual void PreDestroy();
            virtual void Destroy();  // This should only be called by the reference counting system!

            //
            // Type id
            //

            // Retrieves the reflection data for this instance
            static const Class* s_Class;
            virtual const Reflect::Class* GetClass() const;

            // Deduces type membership for this instance
            bool IsClass( const Reflect::Class* type ) const;

            // Create class data block for this type
            static Reflect::Class* CreateClass( const tchar_t* name );

            // Enumerates member data (stub)
            static void AcceptCompositeVisitor( Reflect::Composite& comp );

            //
            // Serialization
            //

            // Specifies if the value is directly between the start and end name
            virtual bool                IsCompact() const;

            // This the process callback for sub and primitive elements to have thier data be aggregated into the parent instance
            virtual bool                ProcessComponent( ObjectPtr object, const tchar_t* fieldName );

            // Serialize to a particular data target, just works on this
            void                        ToXML( tstring& xml ) const;
            void                        ToBinary( std::iostream& stream ) const;
            void                        ToFile( const Path& path ) const;

            // Callbacks are executed at the appropriate time by the archive and cloning APIs
            virtual void                PreSerialize() { }
            virtual void                PostSerialize() { }
            virtual void                PreDeserialize() { }
            virtual void                PostDeserialize() { }

            //
            // Introspection
            //

            // Visits fields recursively, used to interactively traverse structures
            virtual void                Accept( Visitor& visitor );

            // Do comparison logic against other object, checks type and field data
            virtual bool                Equals( const Object* object ) const;

            // Copy this object's data into another object isntance
            virtual void                CopyTo( Object* object );

            // Copy this object's data into a new instance
            virtual ObjectPtr           Clone();


            //
            // Mutation
            //

        public:
            mutable ObjectChangeSignature::Event e_Changed;

            virtual void RaiseChanged( const Field* field = NULL ) const
            {
                e_Changed.Raise( ObjectChangeArgs( this, field ) );
            }

            template< class FieldT >
            void FieldChanged( FieldT* fieldAddress ) const
            {
                // the offset of the field is the address of the field minus the address of this object instance
                uintptr_t fieldOffset = ((uint32_t)fieldAddress - (uint32_t)this);

                // find the field in our reflection information
                const Reflect::Field* field = GetClass()->FindFieldByOffset( fieldOffset );

                // your field address probably doesn't point to the field in this instance,
                //  or your field is not exposed to Reflect, add it in your Composite function
                HELIUM_ASSERT( field );

                // notify listeners that this field changed
                RaiseChanged( field );
            }
            
            template< class ObjectT, class FieldT >
            void ChangeField( FieldT ObjectT::* field, const FieldT& newValue )
            {
                // set the field via pointer-to-member on the deduced templated type (!)
                this->*field = newValue;

                // find the field in our reflection information
                const Reflect::Field* field = GetClass()->FindField( field );

                // your field is not exposed to Reflect, add it in your Composite function
                HELIUM_ASSERT( field );

                // notify listeners that this field changed
                RaiseChanged( field );
            }
        };

        //
        // DangerousCast does not type checking
        //

        template<class DerivedT>
        inline DerivedT* DangerousCast(Reflect::Object* base);

        template<class DerivedT>
        inline const DerivedT* DangerousCast(const Reflect::Object* base);

        //
        // AssertCast type checks in debug and asserts if failure, does no type checking in release
        //

        template<class DerivedT>
        inline DerivedT* AssertCast( Reflect::Object* base );

        template<class DerivedT>
        inline const DerivedT* AssertCast(const Reflect::Object* base);

        //
        // TryCast type checks and throws if failure
        //

        template<class DerivedT>
        inline DerivedT* TryCast(Reflect::Object* base);

        template<class DerivedT>
        inline const DerivedT* TryCast(const Reflect::Object* base);

        //
        // ObjectCast always type checks and returns null if failure
        //

        template<class DerivedT>
        inline DerivedT* ObjectCast(Reflect::Object* base);

        template<class DerivedT>
        inline const DerivedT* ObjectCast(const Reflect::Object* base);
    }
}

#include "Foundation/Reflect/Object.inl"
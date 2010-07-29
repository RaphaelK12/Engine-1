///////////////////////////////////////////////////////////////////////////
// Generated by litesql-gen.exe on Mon Jul 19 17:52:48 2010 (localtime): 
// C:\Projects\github\kramdar\AppFramework\SDK\LiteSQL\0.3.8_prebuilt\bin\litesql-gen.exe
// http://sourceforge.net/apps/trac/litesql/ 
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Precompile.h"

#include "TrackerDBGenerated.h"
namespace Editor {
using namespace litesql;
TrackedFileProperties::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : mValue(TrackedFileProperties::MValue), trackedProperty(TrackedFileProperties::TrackedProperty), trackedFile(TrackedFileProperties::TrackedFile) {
    switch(rec.size()) {
    case 3:
        mValue = rec[2];
    case 2:
        trackedProperty = rec[1];
    case 1:
        trackedFile = rec[0];
    }
}
const tstring TrackedFileProperties::table__( TXT( "TrackedFile_TrackedProperty_" ));
const litesql::FieldType TrackedFileProperties::TrackedFile( TXT( "TrackedFile1" ), TXT( "INTEGER" ),table__);
const litesql::FieldType TrackedFileProperties::TrackedProperty( TXT( "TrackedProperty2" ), TXT( "INTEGER" ),table__);
const litesql::FieldType TrackedFileProperties::MValue( TXT( "mValue_" ), TXT( "TEXT" ),table__);
void TrackedFileProperties::link(const litesql::Database& db, const Editor::TrackedFile& o0, const Editor::TrackedProperty& o1, tstring mValue) {
    Record values;
    Split fields;
    fields.push_back(TrackedFile.name());
    values.push_back(o0.id);
    fields.push_back(TrackedProperty.name());
    values.push_back(o1.id);
    fields.push_back(MValue.name());
    values.push_back(mValue);
    db.insert(table__, values, fields);
}
void TrackedFileProperties::unlink(const litesql::Database& db, const Editor::TrackedFile& o0, const Editor::TrackedProperty& o1, tstring mValue) {
    db.delete_(table__, (TrackedFile == o0.id && TrackedProperty == o1.id && (MValue == mValue)));
}
void TrackedFileProperties::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<TrackedFileProperties::Row> TrackedFileProperties::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(TrackedFile.fullName());
    sel.result(TrackedProperty.fullName());
    sel.result(MValue.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<TrackedFileProperties::Row>(db, sel);
}
template <> litesql::DataSource<Editor::TrackedFile> TrackedFileProperties::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(TrackedFile.fullName());
    sel.where(srcExpr);
    return DataSource<Editor::TrackedFile>(db, Editor::TrackedFile::Id.in(sel) && expr);
}
template <> litesql::DataSource<Editor::TrackedProperty> TrackedFileProperties::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(TrackedProperty.fullName());
    sel.where(srcExpr);
    return DataSource<Editor::TrackedProperty>(db, Editor::TrackedProperty::Id.in(sel) && expr);
}
FileReferences::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : trackedFile2(FileReferences::TrackedFile2), trackedFile1(FileReferences::TrackedFile1) {
    switch(rec.size()) {
    case 2:
        trackedFile2 = rec[1];
    case 1:
        trackedFile1 = rec[0];
    }
}
const tstring FileReferences::table__( TXT( "TrackedFile_TrackedFile_" ));
const litesql::FieldType FileReferences::TrackedFile1( TXT( "TrackedFile1" ), TXT( "INTEGER" ),table__);
const litesql::FieldType FileReferences::TrackedFile2( TXT( "TrackedFile2" ), TXT( "INTEGER" ),table__);
void FileReferences::link(const litesql::Database& db, const Editor::TrackedFile& o0, const Editor::TrackedFile& o1) {
    Record values;
    Split fields;
    fields.push_back(TrackedFile1.name());
    values.push_back(o0.id);
    fields.push_back(TrackedFile2.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void FileReferences::unlink(const litesql::Database& db, const Editor::TrackedFile& o0, const Editor::TrackedFile& o1) {
    db.delete_(table__, (TrackedFile1 == o0.id && TrackedFile2 == o1.id));
}
void FileReferences::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<FileReferences::Row> FileReferences::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(TrackedFile1.fullName());
    sel.result(TrackedFile2.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<FileReferences::Row>(db, sel);
}
litesql::DataSource<Editor::TrackedFile> FileReferences::getTrackedFile1(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(TrackedFile1.fullName());
    sel.where(srcExpr);
    return DataSource<Editor::TrackedFile>(db, Editor::TrackedFile::Id.in(sel) && expr);
}
litesql::DataSource<Editor::TrackedFile> FileReferences::getTrackedFile2(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(TrackedFile2.fullName());
    sel.where(srcExpr);
    return DataSource<Editor::TrackedFile>(db, Editor::TrackedFile::Id.in(sel) && expr);
}
const litesql::FieldType TrackedFile::Own::Id( TXT( "id_" ), TXT( "INTEGER" ), TXT( "TrackedFile_" ));
TrackedFile::PropertiesHandle::PropertiesHandle(const TrackedFile& owner)
         : litesql::RelationHandle<TrackedFile>(owner) {
}
void TrackedFile::PropertiesHandle::link(const TrackedProperty& o0, tstring mValue) {
    TrackedFileProperties::link(owner->getDatabase(), *owner, o0, mValue);
}
void TrackedFile::PropertiesHandle::unlink(const TrackedProperty& o0, tstring mValue) {
    TrackedFileProperties::unlink(owner->getDatabase(), *owner, o0, mValue);
}
void TrackedFile::PropertiesHandle::del(const litesql::Expr& expr) {
    TrackedFileProperties::del(owner->getDatabase(), expr && TrackedFileProperties::TrackedFile == owner->id);
}
litesql::DataSource<TrackedProperty> TrackedFile::PropertiesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return TrackedFileProperties::get<TrackedProperty>(owner->getDatabase(), expr, (TrackedFileProperties::TrackedFile == owner->id) && srcExpr);
}
litesql::DataSource<TrackedFileProperties::Row> TrackedFile::PropertiesHandle::getRows(const litesql::Expr& expr) {
    return TrackedFileProperties::getRows(owner->getDatabase(), expr && (TrackedFileProperties::TrackedFile == owner->id));
}
TrackedFile::FileReferencesHandle::FileReferencesHandle(const TrackedFile& owner)
         : litesql::RelationHandle<TrackedFile>(owner) {
}
void TrackedFile::FileReferencesHandle::link(const TrackedFile& o0) {
    FileReferences::link(owner->getDatabase(), o0, *owner);
}
void TrackedFile::FileReferencesHandle::unlink(const TrackedFile& o0) {
    FileReferences::unlink(owner->getDatabase(), o0, *owner);
}
void TrackedFile::FileReferencesHandle::del(const litesql::Expr& expr) {
    FileReferences::del(owner->getDatabase(), expr && FileReferences::TrackedFile2 == owner->id);
}
litesql::DataSource<TrackedFile> TrackedFile::FileReferencesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return FileReferences::getTrackedFile1(owner->getDatabase(), expr, (FileReferences::TrackedFile2 == owner->id) && srcExpr);
}
litesql::DataSource<FileReferences::Row> TrackedFile::FileReferencesHandle::getRows(const litesql::Expr& expr) {
    return FileReferences::getRows(owner->getDatabase(), expr && (FileReferences::TrackedFile2 == owner->id));
}
const tstring TrackedFile::type__( TXT( "TrackedFile" ));
const tstring TrackedFile::table__( TXT( "TrackedFile_" ));
const tstring TrackedFile::sequence__( TXT( "TrackedFile_seq" ));
const litesql::FieldType TrackedFile::Id( TXT( "id_" ), TXT( "INTEGER" ),table__);
const litesql::FieldType TrackedFile::Type( TXT( "type_" ), TXT( "TEXT" ),table__);
const litesql::FieldType TrackedFile::MPath( TXT( "mPath_" ), TXT( "TEXT" ),table__);
const litesql::FieldType TrackedFile::MSize( TXT( "mSize_" ), TXT( "INTEGER" ),table__);
const litesql::FieldType TrackedFile::MLastModified( TXT( "mLastModified_" ), TXT( "INTEGER" ),table__);
void TrackedFile::defaults() {
    id = 0;
    mSize = 0;
    mLastModified = 0;
}
TrackedFile::TrackedFile(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), mPath(MPath), mSize(MSize), mLastModified(MLastModified) {
    defaults();
}
TrackedFile::TrackedFile(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), mPath(MPath), mSize(MSize), mLastModified(MLastModified) {
    defaults();
    size_t size = (rec.size() > 5) ? 5 : rec.size();
    switch(size) {
    case 5: mLastModified = convert<const tstring&, litesql::DateTime>(rec[4]);
        mLastModified.setModified(false);
    case 4: mSize = convert<const tstring&, int>(rec[3]);
        mSize.setModified(false);
    case 3: mPath = convert<const tstring&, tstring>(rec[2]);
        mPath.setModified(false);
    case 2: type = convert<const tstring&, tstring>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const tstring&, int>(rec[0]);
        id.setModified(false);
    }
}
TrackedFile::TrackedFile(const TrackedFile& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), mPath(obj.mPath), mSize(obj.mSize), mLastModified(obj.mLastModified) {
}
const TrackedFile& TrackedFile::operator=(const TrackedFile& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        mPath = obj.mPath;
        mSize = obj.mSize;
        mLastModified = obj.mLastModified;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
TrackedFile::PropertiesHandle TrackedFile::properties() {
    return TrackedFile::PropertiesHandle(*this);
}
TrackedFile::FileReferencesHandle TrackedFile::fileReferences() {
    return TrackedFile::FileReferencesHandle(*this);
}
tstring TrackedFile::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(mPath.name());
    values.push_back(mPath);
    mPath.setModified(false);
    fields.push_back(mSize.name());
    values.push_back(mSize);
    mSize.setModified(false);
    fields.push_back(mLastModified.name());
    values.push_back(mLastModified);
    mLastModified.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void TrackedFile::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    tstring newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void TrackedFile::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, mPath);
    updateField(updates, table__, mSize);
    updateField(updates, table__, mLastModified);
}
void TrackedFile::addIDUpdates(Updates& updates) {
}
void TrackedFile::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(MPath);
    ftypes.push_back(MSize);
    ftypes.push_back(MLastModified);
}
void TrackedFile::delRecord() {
    deleteFromTable(table__, id);
}
void TrackedFile::delRelations() {
    TrackedFileProperties::del(*db, (TrackedFileProperties::TrackedFile == id));
    FileReferences::del(*db, (FileReferences::TrackedFile1 == id) || (FileReferences::TrackedFile2 == id));
}
void TrackedFile::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void TrackedFile::del() {
    if (typeIsCorrect() == false) {
        std::auto_ptr<TrackedFile> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool TrackedFile::typeIsCorrect() {
    return type == type__;
}
std::auto_ptr<TrackedFile> TrackedFile::upcast() {
    return std::auto_ptr<TrackedFile>(new TrackedFile(*this));
}
std::auto_ptr<TrackedFile> TrackedFile::upcastCopy() {
    TrackedFile* np = new TrackedFile(*this);
    np->id = id;
    np->type = type;
    np->mPath = mPath;
    np->mSize = mSize;
    np->mLastModified = mLastModified;
    np->inDatabase = inDatabase;
    return std::auto_ptr<TrackedFile>(np);
}
tostream & operator<<(tostream& os, TrackedFile o) {
    os <<  TXT( "-------------------------------------" ) << std::endl;
    os << o.id.name() <<  TXT( " = " ) << o.id << std::endl;
    os << o.type.name() <<  TXT( " = " ) << o.type << std::endl;
    os << o.mPath.name() <<  TXT( " = " ) << o.mPath << std::endl;
    os << o.mSize.name() <<  TXT( " = " ) << o.mSize << std::endl;
    os << o.mLastModified.name() <<  TXT( " = " ) << o.mLastModified << std::endl;
    os <<  TXT( "-------------------------------------" ) << std::endl;
    return os;
}
const litesql::FieldType TrackedProperty::Own::Id( TXT( "id_" ), TXT( "INTEGER" ), TXT( "TrackedProperty_" ));
const tstring TrackedProperty::type__( TXT( "TrackedProperty" ));
const tstring TrackedProperty::table__( TXT( "TrackedProperty_" ));
const tstring TrackedProperty::sequence__( TXT( "TrackedProperty_seq" ));
const litesql::FieldType TrackedProperty::Id( TXT( "id_" ), TXT( "INTEGER" ),table__);
const litesql::FieldType TrackedProperty::Type( TXT( "type_" ), TXT( "TEXT" ),table__);
const litesql::FieldType TrackedProperty::MName( TXT( "mName_" ), TXT( "TEXT" ),table__);
void TrackedProperty::defaults() {
    id = 0;
}
TrackedProperty::TrackedProperty(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), mName(MName) {
    defaults();
}
TrackedProperty::TrackedProperty(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), mName(MName) {
    defaults();
    size_t size = (rec.size() > 3) ? 3 : rec.size();
    switch(size) {
    case 3: mName = convert<const tstring&, tstring>(rec[2]);
        mName.setModified(false);
    case 2: type = convert<const tstring&, tstring>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const tstring&, int>(rec[0]);
        id.setModified(false);
    }
}
TrackedProperty::TrackedProperty(const TrackedProperty& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), mName(obj.mName) {
}
const TrackedProperty& TrackedProperty::operator=(const TrackedProperty& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        mName = obj.mName;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
tstring TrackedProperty::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(mName.name());
    values.push_back(mName);
    mName.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void TrackedProperty::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    tstring newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void TrackedProperty::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, mName);
}
void TrackedProperty::addIDUpdates(Updates& updates) {
}
void TrackedProperty::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(MName);
}
void TrackedProperty::delRecord() {
    deleteFromTable(table__, id);
}
void TrackedProperty::delRelations() {
    TrackedFileProperties::del(*db, (TrackedFileProperties::TrackedProperty == id));
}
void TrackedProperty::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void TrackedProperty::del() {
    if (typeIsCorrect() == false) {
        std::auto_ptr<TrackedProperty> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool TrackedProperty::typeIsCorrect() {
    return type == type__;
}
std::auto_ptr<TrackedProperty> TrackedProperty::upcast() {
    return std::auto_ptr<TrackedProperty>(new TrackedProperty(*this));
}
std::auto_ptr<TrackedProperty> TrackedProperty::upcastCopy() {
    TrackedProperty* np = new TrackedProperty(*this);
    np->id = id;
    np->type = type;
    np->mName = mName;
    np->inDatabase = inDatabase;
    return std::auto_ptr<TrackedProperty>(np);
}
tostream & operator<<(tostream& os, TrackedProperty o) {
    os <<  TXT( "-------------------------------------" ) << std::endl;
    os << o.id.name() <<  TXT( " = " ) << o.id << std::endl;
    os << o.type.name() <<  TXT( " = " ) << o.type << std::endl;
    os << o.mName.name() <<  TXT( " = " ) << o.mName << std::endl;
    os <<  TXT( "-------------------------------------" ) << std::endl;
    return os;
}
TrackerDBGenerated::TrackerDBGenerated(tstring backendType, tstring connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> TrackerDBGenerated::getSchema() const {
    std::vector<Database::SchemaItem> res;
    res.push_back(Database::SchemaItem( TXT( "schema_" ), TXT( "table" ), TXT( "CREATE TABLE schema_ (name_ TEXT, type_ TEXT, sql_ TEXT);" )));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem( TXT( "TrackedFile_seq" ), TXT( "sequence" ), TXT( "CREATE SEQUENCE TrackedFile_seq START 1 INCREMENT 1" )));
        res.push_back(Database::SchemaItem( TXT( "TrackedProperty_seq" ), TXT( "sequence" ), TXT( "CREATE SEQUENCE TrackedProperty_seq START 1 INCREMENT 1" )));
    }
    res.push_back(Database::SchemaItem( TXT( "TrackedFile_" ), TXT( "table" ), TXT( "CREATE TABLE TrackedFile_ (id_ " ) + backend->getRowIDType() +  TXT( ",type_ TEXT,mPath_ TEXT,mSize_ INTEGER,mLastModified_ INTEGER)" )));
    res.push_back(Database::SchemaItem( TXT( "TrackedProperty_" ), TXT( "table" ), TXT( "CREATE TABLE TrackedProperty_ (id_ " ) + backend->getRowIDType() +  TXT( ",type_ TEXT,mName_ TEXT)" )));
    res.push_back(Database::SchemaItem( TXT( "TrackedFile_TrackedProperty_" ), TXT( "table" ), TXT( "CREATE TABLE TrackedFile_TrackedProperty_ (TrackedFile1 INTEGER,TrackedProperty2 INTEGER,mValue_ TEXT)" )));
    res.push_back(Database::SchemaItem( TXT( "TrackedFile_TrackedFile_" ), TXT( "table" ), TXT( "CREATE TABLE TrackedFile_TrackedFile_ (TrackedFile1 INTEGER,TrackedFile2 INTEGER)" )));
    res.push_back(Database::SchemaItem( TXT( "_e38a7cf9db0c714b79aa173df66de4c2" ), TXT( "index" ), TXT( "CREATE INDEX _e38a7cf9db0c714b79aa173df66de4c2 ON TrackedFile_TrackedProperty_ (TrackedFile1)" )));
    res.push_back(Database::SchemaItem( TXT( "_7fbcce584a509181aaaad577a611cfbd" ), TXT( "index" ), TXT( "CREATE INDEX _7fbcce584a509181aaaad577a611cfbd ON TrackedFile_TrackedProperty_ (TrackedProperty2)" )));
    res.push_back(Database::SchemaItem( TXT( "_f077f119de086e73a1b63d04fbfd38b1" ), TXT( "index" ), TXT( "CREATE INDEX _f077f119de086e73a1b63d04fbfd38b1 ON TrackedFile_TrackedProperty_ (TrackedFile1,TrackedProperty2)" )));
    res.push_back(Database::SchemaItem( TXT( "_6ded56643913192dfe2f3e4a43015caa" ), TXT( "index" ), TXT( "CREATE INDEX _6ded56643913192dfe2f3e4a43015caa ON TrackedFile_TrackedFile_ (TrackedFile1)" )));
    res.push_back(Database::SchemaItem( TXT( "_570330dcd98c25fbe32c45ad05a82445" ), TXT( "index" ), TXT( "CREATE INDEX _570330dcd98c25fbe32c45ad05a82445 ON TrackedFile_TrackedFile_ (TrackedFile2)" )));
    res.push_back(Database::SchemaItem( TXT( "_1520615c7cf0e6fb4271478adaf7774f" ), TXT( "index" ), TXT( "CREATE INDEX _1520615c7cf0e6fb4271478adaf7774f ON TrackedFile_TrackedFile_ (TrackedFile1,TrackedFile2)" )));
    return res;
}
void TrackerDBGenerated::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
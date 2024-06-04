//
// Created by pwipo on 03.06.2024.
//
#include "SMCApi.h"

SMCApi::Number::Number(const signed char value) {
    type = NumberType::NT_BYTE;
    auto *valueInternal = new signed char;
    *valueInternal = value;
    pValue = valueInternal;
}

SMCApi::Number::Number(const short value) {
    type = NumberType::NT_SHORT;
    auto *valueInternal = new short;
    *valueInternal = value;
    pValue = valueInternal;
}

SMCApi::Number::Number(const long value) {
    type = NumberType::NT_INTEGER;
    auto *valueInternal = new long;
    *valueInternal = value;
    pValue = valueInternal;
}

SMCApi::Number::Number(const long long int value) {
    type = NumberType::NT_LONG;
    auto *valueInternal = new long long int;
    *valueInternal = value;
    pValue = valueInternal;
}

SMCApi::Number::Number(const float value) {
    type = NumberType::NT_FLOAT;
    auto *valueInternal = new float;
    *valueInternal = value;
    pValue = valueInternal;
}

SMCApi::Number::Number(const double value) {
    type = NumberType::NT_DOUBLE;
    auto *valueInternal = new double;
    *valueInternal = value;
    pValue = valueInternal;
}

SMCApi::Number::Number(const SMCApi::NumberType type, char *valueString) {
    Number::type = type;
    pValue = valueString;
}

SMCApi::Number::Number(const SMCApi::Number *pNumber) {
    type = pNumber->type;
    switch (type) {
        case NumberType::NT_BYTE: {
            auto *valueInternal = new signed char;
            *valueInternal = *((signed char *) pNumber->pValue);
            pValue = valueInternal;
            break;
        }
        case NumberType::NT_SHORT: {
            auto *valueInternal = new short;
            *valueInternal = *((short *) pNumber->pValue);
            pValue = valueInternal;
            break;
        }
        case NumberType::NT_INTEGER: {
            auto *valueInternal = new long;
            *valueInternal = *((long *) pNumber->pValue);
            pValue = valueInternal;
            break;
        }
        case NumberType::NT_LONG: {
            auto *valueInternal = new long long int;
            *valueInternal = *((long long int *) pNumber->pValue);
            pValue = valueInternal;
            break;
        }
        case NumberType::NT_BIG_INTEGER: {
            size_t size = sizeof((char *) pNumber->pValue);
            pValue = new char[size];
            memcpy(pValue, pNumber->pValue, size);
            break;
        }
        case NumberType::NT_FLOAT: {
            auto *valueInternal = new float;
            *valueInternal = *((float *) pNumber->pValue);
            pValue = valueInternal;
            break;
        }
        case NumberType::NT_DOUBLE: {
            auto *valueInternal = new double;
            *valueInternal = *((double *) pNumber->pValue);
            pValue = valueInternal;
            break;
        }
        case NumberType::NT_BIG_DECIMAL: {
            size_t size = sizeof((char *) pNumber->pValue);
            pValue = new char[size];
            memcpy(pValue, pNumber->pValue, size);
            break;
        }
    }
}

SMCApi::Number::~Number() {
    switch (type) {
        case NumberType::NT_BYTE:
            delete (signed char *) pValue;
            break;
        case NumberType::NT_SHORT:
            delete (short *) pValue;
            break;
        case NumberType::NT_INTEGER:
            delete (long *) pValue;
            break;
        case NumberType::NT_LONG:
            delete (long long int *) pValue;
            break;
        case NumberType::NT_FLOAT:
            delete (float *) pValue;
            break;
        case NumberType::NT_DOUBLE:
            delete (double *) pValue;
            break;
        case NumberType::NT_BIG_INTEGER:
        case NumberType::NT_BIG_DECIMAL:
            delete (char *) pValue;
            break;
    }
    pValue = nullptr;
}

signed char SMCApi::Number::byteValue() {
    switch (type) {
        case NumberType::NT_BYTE:
            return *((signed char *) pValue);
        case NumberType::NT_SHORT:
            return static_cast<signed char>(*((short *) pValue));
        case NumberType::NT_INTEGER:
            return static_cast<signed char>(*((long *) pValue));
        case NumberType::NT_LONG:
            return static_cast<signed char>(*((int long long *) pValue));
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return static_cast<signed char>(std::stoll(str));
        }
        case NumberType::NT_FLOAT:
            return static_cast<signed char>(*((float *) pValue));
        case NumberType::NT_DOUBLE:
            return static_cast<signed char>(*((double *) pValue));
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return static_cast<signed char>(std::stod(str));
        }
    }
    return 0;
}

short SMCApi::Number::shortValue() {
    switch (type) {
        case NumberType::NT_BYTE:
            return static_cast<short>(*((signed char *) pValue));
        case NumberType::NT_SHORT:
            return *((short *) pValue);
        case NumberType::NT_INTEGER:
            return static_cast<short>(*((long *) pValue));
        case NumberType::NT_LONG:
            return static_cast<short>(*((int long long *) pValue));
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return static_cast<short>(std::stoll(str));
        }
        case NumberType::NT_FLOAT:
            return static_cast<short>(*((float *) pValue));
        case NumberType::NT_DOUBLE:
            return static_cast<short>(*((double *) pValue));
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return static_cast<short>(std::stod(str));
        }
    }
    return 0;
}

long SMCApi::Number::intValue() {
    switch (type) {
        case NumberType::NT_BYTE:
            return static_cast<long>(*((signed char *) pValue));
        case NumberType::NT_SHORT:
            return static_cast<long>(*((short *) pValue));
        case NumberType::NT_INTEGER:
            return *((long *) pValue);
        case NumberType::NT_LONG:
            return static_cast<long>(*((int long long *) pValue));
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return static_cast<long>(std::stoll(str));
        }
        case NumberType::NT_FLOAT:
            return static_cast<long>(*((float *) pValue));
        case NumberType::NT_DOUBLE:
            return static_cast<long>(*((double *) pValue));
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return static_cast<long>(std::stod(str));
        }
    }
    return 0;
}

long long int SMCApi::Number::longValue() {
    switch (type) {
        case NumberType::NT_BYTE:
            return static_cast<int long long>(*((signed char *) pValue));
        case NumberType::NT_SHORT:
            return static_cast<int long long>(*((short *) pValue));
        case NumberType::NT_INTEGER:
            return static_cast<int long long>(*((long *) pValue));
        case NumberType::NT_LONG:
            return *((int long long *) pValue);
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return static_cast<int long long>(std::stoll(str));
        }
        case NumberType::NT_FLOAT:
            return static_cast<int long long>(*((float *) pValue));
        case NumberType::NT_DOUBLE:
            return static_cast<int long long>(*((double *) pValue));
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return static_cast<int long long>(std::stod(str));
        }
    }
    return 0;
}

float SMCApi::Number::floatValue() {
    switch (type) {
        case NumberType::NT_BYTE:
            return static_cast<float>(*((signed char *) pValue));
        case NumberType::NT_SHORT:
            return static_cast<float>(*((short *) pValue));
        case NumberType::NT_INTEGER:
            return static_cast<float>(*((long *) pValue));
        case NumberType::NT_LONG:
            return static_cast<float>(*((int long long *) pValue));
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return static_cast<float>(std::stoll(str));
        }
        case NumberType::NT_FLOAT:
            return *((float *) pValue);
        case NumberType::NT_DOUBLE:
            return static_cast<float>(*((double *) pValue));
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return static_cast<float>(std::stod(str));
        }
    }
    return 0;
}

double SMCApi::Number::doubleValue() {
    switch (type) {
        case NumberType::NT_BYTE:
            return static_cast<double>(*((signed char *) pValue));
        case NumberType::NT_SHORT:
            return static_cast<double>(*((short *) pValue));
        case NumberType::NT_INTEGER:
            return static_cast<double>(*((long *) pValue));
        case NumberType::NT_LONG:
            return static_cast<double>(*((int long long *) pValue));
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return static_cast<double>(std::stoll(str));
        }
        case NumberType::NT_FLOAT:
            return static_cast<double>(*((float *) pValue));
        case NumberType::NT_DOUBLE:
            return *((double *) pValue);
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return static_cast<double>(std::stod(str));
        }
    }
    return 0;
}

std::string SMCApi::Number::toString() {
    switch (type) {
        case NumberType::NT_BYTE:
            return std::to_string(*((signed char *) pValue));
        case NumberType::NT_SHORT:
            return std::to_string(*((float *) pValue));
        case NumberType::NT_INTEGER:
            return std::to_string(*((long *) pValue));
        case NumberType::NT_LONG:
            return std::to_string(*((int long long *) pValue));
        case NumberType::NT_BIG_INTEGER: {
            std::string str((char *) pValue);
            return str;
        }
        case NumberType::NT_FLOAT:
            return std::to_string(*((float *) pValue));
        case NumberType::NT_DOUBLE:
            return std::to_string(*((double *) pValue));
        case NumberType::NT_BIG_DECIMAL: {
            std::string str((char *) pValue);
            return str;
        }
    }
    return "";
}

SMCApi::NumberType SMCApi::Number::getType() const {
    return type;
}

SMCApi::ObjectType SMCApi::convertToObject(ValueType type) {
    switch (type) {
        case VT_STRING:
            return ObjectType::OT_STRING;
        case VT_BYTE:
            return ObjectType::OT_BYTE;
        case VT_SHORT:
            return ObjectType::OT_SHORT;
        case VT_INTEGER:
            return ObjectType::OT_INTEGER;
        case VT_LONG:
            return ObjectType::OT_LONG;
        case VT_BIG_INTEGER:
            return ObjectType::OT_BIG_INTEGER;
        case VT_FLOAT:
            return ObjectType::OT_FLOAT;
        case VT_DOUBLE:
            return ObjectType::OT_DOUBLE;
        case VT_BIG_DECIMAL:
            return ObjectType::OT_BIG_DECIMAL;
        case VT_BYTES:
            return ObjectType::OT_BYTES;
        case VT_OBJECT_ARRAY:
            return ObjectType::OT_OBJECT_ARRAY;
        case VT_BOOLEAN:
            return ObjectType::OT_BOOLEAN;
    }
    return ObjectType::OT_INTEGER;
}

SMCApi::ObjectType SMCApi::convertToObject(NumberType type) {
    switch (type) {
        case NT_BYTE:
            return ObjectType::OT_BYTE;
        case NT_SHORT:
            return ObjectType::OT_SHORT;
        case NT_INTEGER:
            return ObjectType::OT_INTEGER;
        case NT_LONG:
            return ObjectType::OT_LONG;
        case NT_BIG_INTEGER:
            return ObjectType::OT_BIG_INTEGER;
        case NT_FLOAT:
            return ObjectType::OT_FLOAT;
        case NT_DOUBLE:
            return ObjectType::OT_DOUBLE;
        case NT_BIG_DECIMAL:
            return ObjectType::OT_BIG_DECIMAL;
    }
    return ObjectType::OT_INTEGER;
}

SMCApi::ValueType SMCApi::convertToValue(SMCApi::NumberType type) {
    switch (type) {
        case NT_BYTE:
            return ValueType::VT_BYTE;
        case NT_SHORT:
            return ValueType::VT_SHORT;
        case NT_INTEGER:
            return ValueType::VT_INTEGER;
        case NT_LONG:
            return ValueType::VT_LONG;
        case NT_BIG_INTEGER:
            return ValueType::VT_BIG_INTEGER;
        case NT_FLOAT:
            return ValueType::VT_FLOAT;
        case NT_DOUBLE:
            return ValueType::VT_DOUBLE;
        case NT_BIG_DECIMAL:
            return ValueType::VT_BIG_DECIMAL;
    }
    return ValueType::VT_INTEGER;
}

SMCApi::NumberType SMCApi::convertToNumber(SMCApi::ValueType type) {
    switch (type) {
        case VT_BYTE:
            return NumberType::NT_BYTE;
        case VT_SHORT:
            return NumberType::NT_SHORT;
        case VT_INTEGER:
            return NumberType::NT_INTEGER;
        case VT_LONG:
            return NumberType::NT_LONG;
        case VT_BIG_INTEGER:
            return NumberType::NT_BIG_INTEGER;
        case VT_FLOAT:
            return NumberType::NT_FLOAT;
        case VT_DOUBLE:
            return NumberType::NT_DOUBLE;
        case VT_BIG_DECIMAL:
            return NumberType::NT_BIG_DECIMAL;
    }
    return NumberType::NT_INTEGER;
}

bool equalsCharIgnoreCase(char a, char b) {
    return std::tolower(static_cast<unsigned char>(a)) ==
           std::tolower(static_cast<unsigned char>(b));
}

bool equalsIgnoreCase(const std::wstring &a, const std::wstring &b) {
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin(), equalsCharIgnoreCase);
}


SMCApi::ObjectField::ObjectField(const std::wstring &name, const SMCApi::ObjectType type) : name(name), pValue(nullptr), type(type) {}

SMCApi::ObjectField::ObjectField(const std::wstring &name, const std::wstring *value) : name(name) {
    setValue(value);
}

SMCApi::ObjectField::ObjectField(const std::wstring &name, const SMCApi::Number *value) : name(name) {
    setValue(value);
}

SMCApi::ObjectField::ObjectField(const std::wstring &name, const signed char *value) : name(name) {
    setValue(value);
}

SMCApi::ObjectField::ObjectField(const std::wstring &name, const bool value) : name(name) {
    setValue(value);
}

SMCApi::ObjectField::ObjectField(const std::wstring &name, const SMCApi::ObjectArray *value) : name(name) {
    setValue(value);
}

SMCApi::ObjectField::ObjectField(const std::wstring &name, const SMCApi::ObjectElement *value) : name(name) {
    setValue(value);
}

SMCApi::ObjectField::ObjectField(const SMCApi::ObjectField *objectField) : name(objectField->name) {
    setValue(objectField);
}

const std::wstring &SMCApi::ObjectField::getName() const {
    return name;
}

void SMCApi::ObjectField::setName(const std::wstring &name) {
    ObjectField::name = name;
}

bool SMCApi::ObjectField::isNull() {
    return pValue == nullptr;
}

void SMCApi::ObjectField::setValueNull(const SMCApi::ObjectType type) {
    deleteValue();
    ObjectField::type = type;
}

void SMCApi::ObjectField::setValue(const std::wstring *value) {
    deleteValue();
    type = ObjectType::OT_STRING;
    pValue = (void *) value;
}

void SMCApi::ObjectField::setValue(const SMCApi::Number *value) {
    deleteValue();
    type = (ObjectType) convertToObject(value->getType());
    pValue = (void *) value;
}

void SMCApi::ObjectField::setValue(const signed char *value) {
    deleteValue();
    type = ObjectType::OT_BYTES;
    pValue = (void *) value;
}

void SMCApi::ObjectField::setValue(const bool value) {
    deleteValue();
    type = ObjectType::OT_BOOLEAN;
    auto *valueInternal = new bool;
    *valueInternal = value;
    pValue = valueInternal;
}

void SMCApi::ObjectField::setValue(const SMCApi::ObjectArray *value) {
    deleteValue();
    type = ObjectType::OT_OBJECT_ARRAY;
    pValue = (void *) value;
}

void SMCApi::ObjectField::setValue(const SMCApi::ObjectElement *value) {
    deleteValue();
    type = ObjectType::OT_OBJECT_ELEMENT;
    pValue = (void *) value;
}

void SMCApi::ObjectField::setValue(const SMCApi::ObjectField *value) {
    deleteValue();
    type = value->type;
    switch (value->getType()) {
        case OT_STRING: {
            auto pStrNew = new std::wstring(*value->getValueString());
            pValue = pStrNew;
            break;
        }
        case OT_BYTE:
        case OT_SHORT:
        case OT_INTEGER:
        case OT_LONG:
        case OT_BIG_INTEGER:
        case OT_FLOAT:
        case OT_DOUBLE:
        case OT_BIG_DECIMAL:
            pValue = new Number(value->getValueNumber());
            break;
        case OT_BYTES: {
            long size = value->getBytesCount();
            pValue = new char[size];
            memcpy(pValue, value->getValueBytes(), size);
            break;
        }
        case OT_BOOLEAN: {
            bool *pV = new bool;
            *pV = value->getValueBoolean();
            pValue = pV;
            break;
        }
        case OT_OBJECT_ARRAY:
            pValue = new SMCApi::ObjectArray(value->getValueObjectArray());
            break;
        case OT_OBJECT_ELEMENT:
            pValue = new SMCApi::ObjectElement(value->getValueObjectElement());
            break;
    }
}

void SMCApi::ObjectField::setValue(SMCApi::IValue *value) {
    deleteValue();
    type = (ObjectType) convertToObject(value->getType());
    switch (value->getType()) {
        case VT_STRING: {
            auto pStrNew = new std::wstring(*value->getValueString());
            pValue = pStrNew;
            break;
        }
        case VT_BYTE:
        case VT_SHORT:
        case VT_INTEGER:
        case VT_LONG:
        case VT_BIG_INTEGER:
        case VT_FLOAT:
        case VT_DOUBLE:
        case VT_BIG_DECIMAL:
            pValue = new Number(value->getValueNumber());
            break;
        case VT_BYTES: {
            long size = value->getBytesCount();
            pValue = new char[size];
            memcpy(pValue, value->getValueBytes(), size);
            break;
        }
        case VT_OBJECT_ARRAY:
            type = ObjectType::OT_OBJECT_ARRAY;
            pValue = new SMCApi::ObjectArray(value->getValueObjectArray());
            break;
        case VT_BOOLEAN: {
            bool *pV = new bool;
            *pV = value->getValueBoolean();
            type = ObjectType::OT_BOOLEAN;
            pValue = pV;
            break;
        }
    }
}

const std::wstring *SMCApi::ObjectField::getValueString() const {
    if (type != ObjectType::OT_STRING) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (std::wstring *) pValue;
}

const SMCApi::Number *SMCApi::ObjectField::getValueNumber() const {
    if (type != ObjectType::OT_BYTE && type != ObjectType::OT_SHORT && type != ObjectType::OT_INTEGER && type != ObjectType::OT_LONG &&
        type != ObjectType::OT_FLOAT && type != ObjectType::OT_DOUBLE && type != ObjectType::OT_BIG_INTEGER &&
        type != ObjectType::OT_BIG_DECIMAL) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (Number *) pValue;
}

const signed char *SMCApi::ObjectField::getValueBytes() const {
    if (type != ObjectType::OT_BYTES) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (signed char *) pValue;
}

size_t SMCApi::ObjectField::getBytesCount() const {
    if (type != ObjectType::OT_BYTES) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return sizeof((signed char *) pValue);
}

bool SMCApi::ObjectField::getValueBoolean() const {
    if (type != ObjectType::OT_BOOLEAN) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return *((bool *) pValue);
}

const SMCApi::ObjectArray *SMCApi::ObjectField::getValueObjectArray() const {
    if (type != ObjectType::OT_OBJECT_ARRAY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (ObjectArray *) pValue;
}

const SMCApi::ObjectElement *SMCApi::ObjectField::getValueObjectElement() const {
    if (type != ObjectType::OT_OBJECT_ELEMENT) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (ObjectElement *) pValue;
}

SMCApi::ObjectType SMCApi::ObjectField::getType() const {
    return type;
}

bool SMCApi::ObjectField::isSimple() {
    return ObjectType::OT_OBJECT_ARRAY != type && ObjectType::OT_OBJECT_ELEMENT != type;
}

void SMCApi::ObjectField::deleteValue() {
    if (pValue == nullptr)
        return;
    switch (type) {
        case ObjectType::OT_BYTE:
        case ObjectType::OT_SHORT:
        case ObjectType::OT_INTEGER:
        case ObjectType::OT_LONG:
        case ObjectType::OT_FLOAT:
        case ObjectType::OT_DOUBLE:
        case ObjectType::OT_BIG_INTEGER:
        case ObjectType::OT_BIG_DECIMAL:
            delete (Number *) pValue;
            break;
        case OT_OBJECT_ARRAY:
            delete (ObjectArray *) pValue;
            break;
        case OT_OBJECT_ELEMENT:
            delete (ObjectElement *) pValue;
            break;
        case OT_STRING:
            delete (std::wstring *) pValue;
            break;
        case OT_BYTES:
            delete (signed char *) pValue;
            break;
        case OT_BOOLEAN:
            delete (bool *) pValue;
            break;
    }
    pValue = nullptr;
}

SMCApi::ObjectField::~ObjectField() {
    deleteValue();
}

SMCApi::ObjectElement::ObjectElement(const std::vector<ObjectField *> &fields) : fields(fields) {}

SMCApi::ObjectElement::ObjectElement(const SMCApi::ObjectElement *objectElement) {
    for (auto v: objectElement->fields)
        fields.push_back(new ObjectField(v));
}

const std::vector<SMCApi::ObjectField *> &SMCApi::ObjectElement::getFields() const {
    return fields;
}

SMCApi::ObjectField *SMCApi::ObjectElement::findField(const std::wstring &name) {
    for (auto field: fields) {
        if (field->getName() == name)
            return field;
    }
}

SMCApi::ObjectField *SMCApi::ObjectElement::findFieldIgnoreCase(const std::wstring &name) {
    for (auto field: fields) {
        if (equalsIgnoreCase(field->getName(), name))
            return field;
    }
}

bool SMCApi::ObjectElement::isSimple() {
    return std::all_of(fields.cbegin(), fields.cend(), [](ObjectField *field) { return field->isSimple(); });
}

SMCApi::ObjectElement::~ObjectElement() {
    for (auto field: fields)
        delete field;
    fields.clear();
}

void SMCApi::ObjectArray::add(void *pValue, const SMCApi::ObjectType type, int id) {
    if (id == -1) {
        objects.push_back(pValue);
        if (types)
            types->push_back(type);
    } else {
        objects.insert(objects.begin() + id, pValue);
        if (types)
            types->insert(types->begin() + id, type);
    }
}

void SMCApi::ObjectArray::deleteItem(int id) {
    if (objects.size() <= id)
        return;
    void *pValue = objects[id];
    switch (type) {
        case ObjectType::OT_BYTE:
        case ObjectType::OT_SHORT:
        case ObjectType::OT_INTEGER:
        case ObjectType::OT_LONG:
        case ObjectType::OT_FLOAT:
        case ObjectType::OT_DOUBLE:
        case ObjectType::OT_BIG_INTEGER:
        case ObjectType::OT_BIG_DECIMAL:
            delete (Number *) pValue;
            break;
        case OT_OBJECT_ARRAY:
            delete (ObjectArray *) pValue;
            break;
        case OT_OBJECT_ELEMENT:
            delete (ObjectElement *) pValue;
            break;
        case OT_STRING:
            delete (std::wstring *) pValue;
            break;
        case OT_BYTES:
            delete (signed char *) pValue;
            break;
        case OT_BOOLEAN:
            delete (bool *) pValue;
            break;
    }
    pValue = nullptr;
    objects.erase(objects.begin() + id);
    if (types && types->size() > id)
        types->erase(types->begin() + id);
}

SMCApi::ObjectArray::ObjectArray(const SMCApi::ObjectType type) : type(type), types(nullptr) {
    if (type == ObjectType::OT_VALUE_ANY)
        types = new std::vector<ObjectType>;
}

SMCApi::ObjectArray::ObjectArray(const SMCApi::ObjectArray *objectArray) : type(objectArray->type), types(nullptr) {
    if (objectArray->types) {
        types = new std::vector<ObjectType>;
        for (auto t: *(objectArray->types))
            types->push_back(t);
        for (int i = 0; i < objectArray->objects.size(); i++)
            add(objectArray->objects[i], types->at(i));
    } else {
        for (auto v: objectArray->objects)
            add(v, objectArray->type);
    }
}

size_t SMCApi::ObjectArray::size() const {
    return objects.size();
}

void SMCApi::ObjectArray::add(const std::wstring *value, int id) {
    if (type != ObjectType::OT_STRING && type != ObjectType::OT_VALUE_ANY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    add((void *) value, ObjectType::OT_STRING, id);
}

void SMCApi::ObjectArray::add(const SMCApi::Number *value, int id) {
    if (type != ObjectType::OT_BYTE && type != ObjectType::OT_SHORT && type != ObjectType::OT_INTEGER && type != ObjectType::OT_LONG &&
        type != ObjectType::OT_FLOAT && type != ObjectType::OT_DOUBLE && type != ObjectType::OT_BIG_INTEGER &&
        type != ObjectType::OT_BIG_DECIMAL && type != ObjectType::OT_VALUE_ANY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    add((void *) value, (ObjectType) convertToObject(value->getType()), id);
}

void SMCApi::ObjectArray::add(const signed char *value, int id) {
    if (type != ObjectType::OT_BYTES && type != ObjectType::OT_VALUE_ANY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    add((void *) value, ObjectType::OT_BYTES, id);
}

void SMCApi::ObjectArray::add(const bool value, int id) {
    if (type != ObjectType::OT_BOOLEAN && type != ObjectType::OT_VALUE_ANY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    auto *valueInternal = new bool;
    *valueInternal = value;
    add((void *) valueInternal, ObjectType::OT_BOOLEAN, id);
}

void SMCApi::ObjectArray::add(const SMCApi::ObjectArray *value, int id) {
    if (type != ObjectType::OT_OBJECT_ARRAY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    add((void *) value, ObjectType::OT_OBJECT_ARRAY, id);
}

void SMCApi::ObjectArray::add(const SMCApi::ObjectElement *value, int id) {
    if (type != ObjectType::OT_OBJECT_ELEMENT) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    add((void *) value, ObjectType::OT_OBJECT_ELEMENT, id);
}

const std::wstring *SMCApi::ObjectArray::getString(int id) const {
    if (type != ObjectType::OT_STRING && (type != ObjectType::OT_VALUE_ANY || (types == nullptr || types->at(id) != ObjectType::OT_STRING))) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (std::wstring *) objects[id];
}

const SMCApi::Number *SMCApi::ObjectArray::getNumber(int id) const {
    if (type != ObjectType::OT_BYTE && type != ObjectType::OT_SHORT && type != ObjectType::OT_INTEGER && type != ObjectType::OT_LONG &&
        type != ObjectType::OT_FLOAT && type != ObjectType::OT_DOUBLE && type != ObjectType::OT_BIG_INTEGER &&
        type != ObjectType::OT_BIG_DECIMAL &&
        (type != ObjectType::OT_VALUE_ANY || (types == nullptr || types->at(id) != ObjectType::OT_STRING))) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (Number *) objects[id];
}

const signed char *SMCApi::ObjectArray::getBytes(int id) const {
    if (type != ObjectType::OT_BYTES && (type != ObjectType::OT_VALUE_ANY || (types == nullptr || types->at(id) != ObjectType::OT_STRING))) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (signed char *) objects[id];
}

const size_t SMCApi::ObjectArray::getBytesCount(int id) const {
    if (type != ObjectType::OT_BYTES && (type != ObjectType::OT_VALUE_ANY || (types == nullptr || types->at(id) != ObjectType::OT_STRING))) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return sizeof((signed char *) objects[id]);
}

const SMCApi::ObjectArray *SMCApi::ObjectArray::getObjectArray(int id) const {
    if (type != ObjectType::OT_OBJECT_ARRAY) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (ObjectArray *) objects[id];
}

const SMCApi::ObjectElement *SMCApi::ObjectArray::getObjectElement(int id) const {
    if (type != ObjectType::OT_OBJECT_ELEMENT) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return (ObjectElement *) objects[id];
}

const SMCApi::ObjectType SMCApi::ObjectArray::getType(int id) const {
    return id >= 0 && types && types->size() > id ? types->at(id) : type;
}

void SMCApi::ObjectArray::remove(int id) {
    deleteItem(id);
}

bool SMCApi::ObjectArray::getBoolean(int id) const {
    if (type != ObjectType::OT_BOOLEAN &&
        (type != ObjectType::OT_VALUE_ANY || (types == nullptr || types->at(id) != ObjectType::OT_STRING))) {
        std::wstring error(L"wrong type");
        throw ModuleException(error);
    }
    return *((bool *) objects[id]);
}

bool SMCApi::ObjectArray::isSimple() {
    return ObjectType::OT_OBJECT_ARRAY != type && ObjectType::OT_OBJECT_ELEMENT != type;
}

SMCApi::ObjectArray::~ObjectArray() {
    for (int i = objects.size() - 1; i >= 0; --i)
        deleteItem(i);
    objects.clear();
    if (types) {
        types->clear();
        delete types;
        types = nullptr;
    }
}

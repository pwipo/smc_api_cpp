//
// Created by pwipo on 01.11.2019.
//

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#ifndef SMCMODULEDEFINITIONPROVIDER_SMCAPI_H
#define SMCMODULEDEFINITIONPROVIDER_SMCAPI_H

#ifdef _EXPORTING
#define CLASS_DECLSPEC    __declspec(dllexport)
#else
#define CLASS_DECLSPEC    __declspec(dllimport)
#endif

namespace SMCApi {

    /**
     * main exception
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC ModuleException : public std::exception {
    private:
        const std::wstring message;
    public:
        explicit ModuleException(const std::wstring &msg);

        const std::wstring *getMessage() const;

        ~ModuleException() override;
    };

    /**
     * represent date value
     *
     * @version 1.0.0
     */
    enum ValueType {
        VT_STRING,
        VT_BYTE,
        VT_SHORT,
        VT_INTEGER,
        VT_LONG,
        VT_BIG_INTEGER,
        VT_FLOAT,
        VT_DOUBLE,
        VT_BIG_DECIMAL,
        VT_BYTES,
        VT_OBJECT_ARRAY,
        VT_BOOLEAN
    };

    enum NumberType {
        NT_BYTE,
        NT_SHORT,
        NT_INTEGER,
        NT_LONG,
        NT_BIG_INTEGER,
        NT_FLOAT,
        NT_DOUBLE,
        NT_BIG_DECIMAL
    };

    /**
     * class for numbers
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC Number {
    private:
        void *pValue;
        NumberType type;
    public:
        explicit Number(signed char value);

        explicit Number(short value);

        explicit Number(long value);

        explicit Number(long long int value);

        explicit Number(float value);

        explicit Number(double value);

        Number(NumberType type, char *valueString);

        explicit Number(const Number *pNumber);

        ~Number();

        signed char byteValue();

        short shortValue();

        long intValue();

        long long int longValue();

        float floatValue();

        double doubleValue();

        std::string toString();

        NumberType getType();
    };

    /**
     * Object type
     *
     * @version 1.0.0
     */
    enum ObjectType {
        OT_OBJECT_ARRAY,
        OT_OBJECT_ELEMENT,
        OT_VALUE_ANY,
        OT_STRING,
        OT_BYTE,
        OT_SHORT,
        OT_INTEGER,
        OT_LONG,
        OT_FLOAT,
        OT_DOUBLE,
        OT_BIG_INTEGER,
        OT_BIG_DECIMAL,
        OT_BYTES,
        OT_BOOLEAN
    };

    ObjectType convertToObject(ValueType type);

    ObjectType convertToObject(NumberType type);

    ValueType convertToValue(NumberType type);

    NumberType convertToNumber(ValueType type);

    ValueType convertToValue(ObjectType type);

    class CLASS_DECLSPEC ObjectElement;

    class CLASS_DECLSPEC ObjectArray;

    /**
     * Interface for value objects
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IValue {
    public:
        /**
         * value type
         *
         * @return ValueType
         */
        virtual ValueType getType() = 0;

        /**
         * value as string
         * only for string values
         *
         * @return Object: String
         */
        virtual std::wstring *getValueString() = 0;

        /**
         * value as number
         * only for number values
         *
         * @return Object: Number
         */
        virtual Number *getValueNumber() = 0;

        /**
         * value as byte array
         * only for byte array values
         *
         * @return Object: byte[]
         */
        virtual signed char *getValueBytes() = 0;

        /**
         * byte array length
         * only for byte array values
         *
         * @return long
         */
        virtual size_t getBytesCount() = 0;

        /**
         * value as byte array
         * only for boolean values
         *
         * @return bool
         */
        virtual bool getValueBoolean() = 0;

        /**
         * value as byte array
         * only for ObjectArray values
         *
         * @return Object: ObjectArray
         */
        virtual ObjectArray *getValueObjectArray() = 0;

//    virtual ~IValue(){};
    };

    /**
     * Field for Object
     * the value can be one of the following types: ObjectArray, ObjectElement, String, Byte, Short, Integer, Long, Float, Double, BigInteger, BigDecimal, byte[], bool.
     * value may be null
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC ObjectField {
    private:
        std::wstring name;
        void *pValue;
        ObjectType type;
        size_t valueBytesLength;
    public:
        ObjectField(const std::wstring &name);

        ObjectField(const std::wstring &name, ObjectType type);

        ObjectField(const std::wstring &name, const std::wstring *value);

        ObjectField(const std::wstring &name, const Number *value);

        ObjectField(const std::wstring &name, const signed char *value, size_t size);

        ObjectField(const std::wstring &name, bool value);

        ObjectField(const std::wstring &name, const ObjectArray *value);

        ObjectField(const std::wstring &name, const ObjectElement *value);

        explicit ObjectField(const ObjectField *objectField);

        const std::wstring &getName() const;

        void setName(const std::wstring &name);

        bool isNull();

        void setValueNull(ObjectType type);

        void setValue(const std::wstring *value);

        void setValue(const Number *value);

        void setValue(const signed char *value, size_t size);

        void setValue(bool value);

        void setValue(const ObjectArray *value);

        void setValue(const ObjectElement *value);

        void setValue(const ObjectField *value);

        void setValue(IValue *value);

        const std::wstring *getValueString() const;

        const Number *getValueNumber() const;

        const signed char *getValueBytes() const;

        size_t getBytesCount() const;

        bool getValueBoolean() const;

        const ObjectArray *getValueObjectArray() const;

        const ObjectElement *getValueObjectElement() const;

        const void *getValue() const;

        ObjectType getType() const;

        bool isSimple();

        void deleteValue();

        ~ObjectField();
    };

    /**
     * Object in ObjectArray
     * contain list of fields (ObjectField)
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC ObjectElement {
    private:
        std::vector<ObjectField *> fields;
    public:
        explicit ObjectElement(const std::vector<ObjectField *> &fields);

        explicit ObjectElement(const ObjectElement *objectElement);

        explicit ObjectElement();

        std::vector<ObjectField *> *getFields();

        ObjectField *findField(const std::wstring &name);

        ObjectField *findFieldIgnoreCase(const std::wstring &name);

        bool isSimple();

        ~ObjectElement();

    };

    /**
     * array of objects
     * main class
     * contain list of object of same type.
     * the values can be one of the following types: ObjectElement, ObjectArray, String, Byte, Short, Integer, Long, Float, Double, BigInteger, BigDecimal, byte[], bool.
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC ObjectArray {
    private:
        std::vector<void *> objects;
        std::vector <ObjectType> *types;
        std::vector <size_t> *sizes;
        ObjectType type;

        void add(void *pValue, ObjectType type, int id = -1, size_t size = 0);

        void addCopy(void *pValue, ObjectType type, size_t size = 0);

        void deleteItem(int id);

    public:
        explicit ObjectArray(ObjectType type);

        explicit ObjectArray(const ObjectArray *objectArray);

        size_t size() const;

        void add(const std::wstring *value, int id = -1);

        void add(const Number *value, int id = -1);

        void add(const signed char *value, size_t size, int id = -1);

        void add(const bool value, int id = -1);

        void add(const ObjectArray *value, int id = -1);

        void add(const ObjectElement *value, int id = -1);

        const std::wstring *getString(int id) const;

        const Number *getNumber(int id) const;

        const signed char *getBytes(int id) const;

        const size_t getBytesCount(int id) const;

        bool getBoolean(int id) const;

        const ObjectArray *getObjectArray(int id) const;

        const ObjectElement *getObjectElement(int id) const;

        const void *get(int id) const;

        void remove(int id);

        ObjectType getType(int id = -1);

        bool isSimple();

        ~ObjectArray();

    };

    /**
     * Interface for value objects factory
     * create value object
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IValueFactory {
    public:
        //    ValueFactory();

        virtual IValue *createData(const std::wstring &) = 0;

        virtual IValue *createData(const std::string &) = 0;

        virtual IValue *createData(const signed char *, long) = 0;

        virtual IValue *createData(const Number *) = 0;

        virtual IValue *createData(const IValue *) = 0;

        virtual IValue *createData(const ObjectArray *) = 0;

        virtual IValue *createData(bool) = 0;

        //    virtual ~IValueFactory() {};
    };

    /**
     * main data type
     *
     * @version 1.0.0
     */
    enum MessageType {
        MESSAGE_PROCESS_STATE_CHANGE/*(4)*/,

        MESSAGE_ACTION_START/*(5)*/,
        MESSAGE_ACTION_STOP/*(6)*/,
        MESSAGE_ACTION_ERROR/*(7)*/,

        MESSAGE_CONFIGURATION_CONTROL_CONFIGURATION_SETTING_UPDATE/*(8)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONFIGURATION_VARIABLE_UPDATE/*(8)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONFIGURATION_VARIABLE_REMOVE/*(8)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONFIGURATION_CREATE/*(8)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONFIGURATION_UPDATE/*(9)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONFIGURATION_REMOVE/*(10)*/,
        MESSAGE_CONFIGURATION_CONTROL_EXECUTION_CONTEXT_CREATE/*(11)*/,
        MESSAGE_CONFIGURATION_CONTROL_EXECUTION_CONTEXT_UPDATE/*(12)*/,
        MESSAGE_CONFIGURATION_CONTROL_EXECUTION_CONTEXT_REMOVE/*(13)*/,
        MESSAGE_CONFIGURATION_CONTROL_SOURCE_CONTEXT_CREATE/*(14)*/,
        MESSAGE_CONFIGURATION_CONTROL_SOURCE_CONTEXT_UPDATE/*(15)*/,
        MESSAGE_CONFIGURATION_CONTROL_SOURCE_CONTEXT_REMOVE/*(16)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONTAINER_CREATE/*(17)*/,
        MESSAGE_CONFIGURATION_CONTROL_CONTAINER_REMOVE/*(18)*/,

        MESSAGE_FLOW_CONTROL_EXECUTE_NOW_START/*(17)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_NOW_EXECUTE/*(18)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_NOW_UPDATE/*(19)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_NOW_STOP/*(20)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_PARALLEL_START/*(21)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_PARALLEL_EXECUTE/*(22)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_PARALLEL_UPDATE/*(23)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_PARALLEL_STOP/*(24)*/,
        MESSAGE_FLOW_CONTROL_EXECUTE_PARALLEL_WAITING_TACTS/*(25)*/,

        MESSAGE_ERROR/*(1000)*/,
        MESSAGE_DATA/*(1001)*/,
        MESSAGE_LOG/*(1002)*/
    };

    /**
     * Types of Process Action
     *
     * @version 1.0.0
     */
    enum ActionType {
        ACTION_START,
        ACTION_EXECUTE,
        ACTION_UPDATE,
        ACTION_STOP
    };

    /**
     * Types of Command
     *
     * @version 1.0.0
     */
    enum CommandType {
        COMMAND_START,
        COMMAND_EXECUTE,
        COMMAND_UPDATE,
        COMMAND_STOP
    };

    /**
     * Source get type
     *
     * @version 1.0.0
     */
    enum SourceGetType {
        SGT_ALL,
        SGT_NEW,
        SGT_NEW_ALL,
        SGT_LAST,
        SGT_LAST_ALL
    };

    /**
     * Source type
     *
     * @version 1.0.0
     */
    enum SourceType {
        ST_MODULE_CONFIGURATION,
        ST_EXECUTION_CONTEXT,
        ST_STATIC_VALUE,
        ST_MULTIPART,
        ST_CALLER,
        ST_CALLER_RELATIVE_NAME,
        ST_OBJECT_ARRAY
    };

    /**
     * Source filter type
     *
     * @version 1.0.0
     */
    enum SourceFilterType {
        SFT_POSITION,
        SFT_NUMBER,
        SFT_STRING_EQUAL,
        SFT_STRING_CONTAIN,
        SFT_OBJECT_PATHS
    };

    /**
     * Interface for Message
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IMessage : public IValue {
    public:
        /**
         * get date of creation
         *
         * @return Date
         */
        virtual long long int getDate() = 0;

        /**
         * get message type
         * for process messages - DATA
         *
         * @return MessageType
         */
        virtual MessageType getMessageType() = 0;

//    virtual ~IMessage() {};
    };

    /**
     * Interface for Action
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IAction {
    public:
        /**
         * get messages
         *
         * @return IMessage list
         */
        virtual std::vector<IMessage *> *getMessages() = 0;

        /**
         * get type
         *
         * @return ActionType
         */
        virtual ActionType getType() = 0;

//    virtual ~IAction() {};
    };

    /**
     * Interface for Command
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC ICommand {
    public:
        /**
         * get actions
         *
         * @return IAction list
         */
        virtual std::vector<IAction *> *getActions() = 0;

        /**
         * get type
         *
         * @return CommandType
         */
        virtual CommandType getType() = 0;

//    virtual ~ICommand() {};
    };

    /**
     * Interface for Module
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGIModule {
    public:
        /**
         * module name
         * unique for system
         *
         * @return name
         */
        virtual std::wstring getName() = 0;

        /**
         * get count types
         * @return
         */
        virtual long countTypes() = 0;

        /**
         * get type name
         *
         * @param typeId serial number in the list of types
         * @return type name
         */
        virtual std::wstring getTypeName(long) = 0;

        /**
         * get minimum count sources
         *
         * @param typeId serial number in the list of types
         * @return long
         */
        virtual long getMinCountSources(long) = 0;

        /**
         * get maximum count sources
         *
         * @param typeId serial number in the list of types
         * @return long
         */
        virtual long getMaxCountSources(long) = 0;

        /**
         * get minimum count execution contexts
         *
         * @param typeId serial number in the list of types
         * @return long
         */
        virtual long getMinCountExecutionContexts(long) = 0;

        /**
         * get maximum count execution contexts
         *
         * @param typeId serial number in the list of types
         * @return long
         */
        virtual long getMaxCountExecutionContexts(long) = 0;

        /**
         * get minimum count managed configurations
         *
         * @param typeId serial number in the list of types
         * @return long
         */
        virtual long getMinCountManagedConfigurations(long) = 0;

        /**
         * get maximum count managed configurations
         *
         * @param typeId serial number in the list of types
         * @return long
         */
        virtual long getMaxCountManagedConfigurations(long) = 0;

    };

    /**
     * Interface for Container
     */
    class CLASS_DECLSPEC CFGIContainer {
    public:
        /**
         * get name
         *
         *  @return string
         */
        virtual std::wstring getName() = 0;

        /**
         * is work
         *
         *  @return boolean
         */
        virtual bool isEnable() = 0;

    };

    class CLASS_DECLSPEC CFGIConfiguration;

    class CLASS_DECLSPEC CFGIConfigurationManaged;

    class CLASS_DECLSPEC CFGIContainerManaged : virtual public CFGIContainer {
    public:
        /**
         * count child configurations
         *
         * @return long
         */
        virtual long countConfigurations() = 0;

        /**
         * get child configuration
         *
         * @param id                    serial number in the list of child configurations
         * @return CFGIConfiguration or null
         */
        virtual CFGIConfiguration *getConfiguration(long) = 0;

        /**
         * count child managed configurations
         *
         * @return long
         */
        virtual long countManagedConfigurations() = 0;

        /**
         * get child managed configuration
         *
         * @param id                    serial number in the list of child managed configurations
         * @return CFGIConfigurationManaged or null
         */
        virtual CFGIConfigurationManaged *getManagedConfiguration(long) = 0;

        /**
         * count child containers
         *
         * @return long
         */
        virtual long countContainers() = 0;

        /**
         * get child container
         *
         * @param id                    serial number in the list of child containers
         * @return CFGIContainer or null
         */
        virtual CFGIContainer *getContainer(long) = 0;

        /**
         * create child container
         *
         * @param name                  unique name for container
         * @return CFGIContainerManaged
         */
        virtual CFGIContainerManaged *createContainer(const std::wstring &) = 0;

        /**
         * delete empty child container
         *
         * @param id                    serial number in the list of child containers
         */
        virtual void removeContainer(long) = 0;

    };

    /**
     * Interface for Module Configuration
     */
    class CLASS_DECLSPEC CFGIConfiguration {
    public:
        /**
         * get module
         *
         *  @return CFGIModule
         */
        virtual CFGIModule *getModule() = 0;

        /**
         * get name
         *
         *  @return string
         */
        virtual std::wstring getName() = 0;

        /**
         * get description
         *
         *  @return string
         */
        virtual std::wstring getDescription() = 0;

        /**
         * get all settings
         *
         * @return List of names
         */
        virtual std::vector <std::wstring> getAllSettingNames() = 0;

        /**
         * get setting value
         *
         * @param key setting name
         * @return IValue or null
         */
        virtual IValue *getSetting(const std::wstring &) = 0;

        /**
         * get all variables
         *
         * @return List of names
         */
        virtual std::vector <std::wstring> getAllVariableNames() = 0;

        /**
         * get variable
         *
         * @param key variable name
         * @return IValue or null
         */
        virtual IValue *getVariable(const std::wstring &) = 0;

        /**
         * get buffer size
         *
         *  @return long
         */
        virtual long getBufferSize() = 0;

        /**
         * get thread buffer size
         *
         * @return int long long
         */
        virtual int long long getThreadBufferSize() = 0;

        /**
         * is work
         *
         *  @return boolean
         */
        virtual bool isEnable() = 0;

        /**
         * check is configuration work now (process execute any commands)
         *
         * @return boolean
         */
        virtual bool isActive() = 0;

    };

    class CLASS_DECLSPEC CFGIExecutionContextManaged;

    class CLASS_DECLSPEC CFGIConfigurationManaged : virtual public CFGIConfiguration {
    public:
        /**
         * change name
         *
         * @param name                   new name
         */
        virtual void setName(std::wstring &) = 0;

        /**
         * change setting
         *
         * @param key                    setting name
         * @param value                  value object (String, Number, byte[])
         */
        virtual void setSetting(const std::wstring &, IValue *) = 0;

        /**
         * change variable
         *
         * @param key                   variable name
         * @param value                 value object (String, Number, byte[])
         */
        virtual void setVariable(const std::wstring &, IValue *) = 0;

        /**
         * remove variable
         *
         * @param key                   variable name
         */
        virtual void removeVariable(const std::wstring &) = 0;

        /**
         * change buffer size
         *
         * @param bufferSize            1 is minimum
         */
        virtual void setBufferSize(long) = 0;

        /**
         * enable or disable configuration
         *
         * @param enable                true for enable
         */
        virtual void setEnable(bool) = 0;

        /**
         * count execution contexts
         *
         * @return long
         */
        virtual long countExecutionContexts() = 0;

        /**
         * get execution context
         *
         * @param id                    serial number in the list of Execution Contexts
         * @return CFGIExecutionContextManaged or null
         */
        virtual CFGIExecutionContextManaged *getExecutionContext(long) = 0;

        /**
         * create execution context and bind it to this configuration
         *
         * @param name                  unique name for configuration
         * @param type                  type
         * @param maxWorkInterval       max work interval. if -1, no time limit. in milliseconds
         * @return CFGIExecutionContextManaged
         */
        virtual CFGIExecutionContextManaged *createExecutionContext(const std::wstring &, const std::wstring &, long) = 0;

        /**
         * update execution context in list
         *
         * @param id              serial number in the list of execution contexts
         * @param name            unique name for configuration
         * @param type            type
         * @param maxWorkInterval max work interval. if -1, no time limit. in milliseconds
         * @return CFGIExecutionContextManaged
         */
        virtual CFGIExecutionContextManaged *updateExecutionContext(long, const std::wstring &, const std::wstring &, long) = 0;

        /**
         * delete execution context
         *
         * @param id                    serial number in the list of Execution Contexts
         */
        virtual void removeExecutionContext(long) = 0;

        /**
         * get container

         * @return CFGIContainerManaged
         */
        virtual CFGIContainerManaged *getContainer() = 0;

    };

    class CLASS_DECLSPEC CFGISource;

    class CLASS_DECLSPEC CFGISourceManaged;

    /**
     * Interface for Source multipart
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGISourceList {
    public:
        /**
         * count sources
         *
         * @return int
         */
        virtual long countSource() = 0;

        /**
         * get source
         *
         * @param id                    serial number in the list of sources
         * @return CFGISource or null
         */
        virtual CFGISource *getSource(long) = 0;

    };

    class CLASS_DECLSPEC CFGIExecutionContext;

    /**
     * Interface for Managed Source multipart
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGISourceListManaged : virtual public CFGISourceList {
    public:
        /**
         * create source and bind it to this execution context
         * add source to end of current list (order = max_order + 1)
         * created ContextSourceType is ST_MODULE_CONFIGURATION
         *
         * @param configuration         configuration source.
         * @param getType               type of get commands from source.
         * @param countLast             only for ContextSourceGetType.SGT_LAST. minimum 1.
         * @param eventDriven           if true, then source is event driven
         * @return CFGISourceManaged
         */
        virtual CFGISourceManaged *createSourceConfiguration(CFGIConfiguration *, SourceGetType, long, bool) = 0;

        /**
         * create source and bind it to this execution context
         * add source to end of current list (order = max_order + 1)
         * created ContextSourceType is ST_EXECUTION_CONTEXT
         *
         * @param executionContext      execution context source.
         * @param getType               type of get commands from source.
         * @param countLast             only for ContextSourceGetType.SGT_LAST. minimum 1.
         * @param eventDriven           if true, then source is event driven
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *createSourceExecutionContext(CFGIExecutionContext *, SourceGetType, long, bool) = 0;

        /**
         * create source and bind it to this execution context
         * add source to end of current list (order = max_order + 1)
         * created ContextSourceType is ST_STATIC_VALUE
         *
         * @param value                 value (String, Number or byte array)
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *createSourceValue(IValue *) = 0;

        /**
         * create source and bind it to this execution context
         * add source to end of list (order = max_order + 1)
         * created ContextSourceType is ST_MULTIPART
         *
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *createSourceMultipart() = 0;

        /**
         * Create source and bind it to this execution context
         * add source to end of current list (order = max_order + 1)
         * created ContextSourceType is ST_OBJECT_ARRAY
         *
         * @param value  ObjectArray
         * @param fields List of field names to be changed. Сan be hierarchical, in which case the names are separated by a dot.
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *createSource(ObjectArray *, std::vector <std::wstring> *) = 0;

        /**
         * Update source in list
         * ContextSourceType is ST_MODULE_CONFIGURATION
         *
         * @param id            serial number in the list
         * @param configuration configuration source.
         * @param getType       type of get commands from source.
         * @param countLast     only for ContextSourceGetType.SGT_LAST. minimum 1.
         * @param eventDriven   if set, then source is event driven
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *updateSourceConfiguration(long, CFGIConfiguration *, SourceGetType, long, bool) = 0;

        /**
         * Update source in list
         * created ContextSourceType is ST_EXECUTION_CONTEXT
         *
         * @param id               serial number in the list
         * @param executionContext execution context source.
         * @param getType          type of get commands from source.
         * @param countLast        only for ContextSourceGetType.SGT_LAST. minimum 1.
         * @param eventDriven      if set, then source is event driven
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *updateSourceExecutionContext(long, CFGIExecutionContext *, SourceGetType, long, bool) = 0;

        /**
         * Update source in list
         * created ContextSourceType is ST_STATIC_VALUE
         *
         * @param id    serial number in the list
         * @param value value
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *updateSourceValue(long, IValue *) = 0;

        /**
         * Update source in list
         * created ContextSourceType is ST_OBJECT_ARRAY
         *
         * @param id     serial number in the list
         * @param value  ObjectArray
         * @param fields List of field names to be changed. Сan be hierarchical, in which case the names are separated by a dot.
         * @return CFGISourceManage
         */
        virtual CFGISourceManaged *updateSource(long, ObjectArray *, std::vector <std::wstring> *) = 0;

        /**
         * remove source from list
         *
         * @param id                    serial number in the list of sources
         */
        virtual void removeSource(long) = 0;

        /**
         * get managed source list
         *
         * @param id serial number in the list of sources
         * @return CFGISourceListManaged or null
         */
        virtual CFGISourceListManaged *getSourceListManaged(long) = 0;

        /**
         * get managed source
         *
         * @param id serial number in the list of sources
         * @return CFGISourceManaged or null
         */
        virtual CFGISourceManaged *getSourceManaged(long) = 0;

    };

    /**
     * Interface for Execution Context
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGIExecutionContext : virtual public CFGISourceList {
    public:
        /**
         * get configuration
         * @return CFGIConfiguration
         */
        virtual CFGIConfiguration *getConfiguration() = 0;

        /**
         * get name
         *
         * @return name
         */
        virtual std::wstring getName() = 0;

        /**
         * get max work interval in milliseconds
         * if -1, no time limit
         *
         * @return int
         */
        virtual long getMaxWorkInterval() = 0;

        /**
         * is work
         *
         * @return true if work
         */
        virtual bool isEnable() = 0;

        /**
         * check is context work now (execute any command)
         *
         * @return boolean
         */
        virtual bool isActive() = 0;

        /**
         * get type
         * unique for configuration
         *
         * @return type or empty for default/any type
         */
        virtual std::wstring getType() = 0;

    };

    /**
     * Interface for Managed Execution Context
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGIExecutionContextManaged : virtual public CFGIExecutionContext, virtual public CFGISourceListManaged {
    public:
        /**
         * change name
         *
         * @param name                  unique name for configuration
         */
        virtual void setName(std::wstring &) = 0;

        /**
         * change max work interval
         *
         * @param maxWorkInterval       if -1, no time limit. in milliseconds
         */
        virtual void setMaxWorkInterval(long) = 0;

        /**
         * enable or disable configuration
         *
         * @param enable                true for enable
         */
        virtual void setEnable(bool) = 0;

        /**
         * count execution contexts
         *
         * @return int
         */
        virtual long countExecutionContexts() = 0;

        /**
         * get execution context
         *
         * @param id                    serial number in the list of Execution Contexts
         * @return CFGIExecutionContext or null
         */
        virtual CFGIExecutionContext *getExecutionContext(long) = 0;

        /**
         * insert execution context in list
         * Shifts the element currently at that position (if any) and any subsequent elements to the right (adds one to their indices).
         *
         * @param id                    serial number in the list of Execution Contexts
         * @param executionContext      execution context
         */
        virtual void insertExecutionContext(long, CFGIExecutionContext *) = 0;

        /**
         * update execution context in list
         *
         * @param id               serial number in the list of Execution Contexts
         * @param executionContext execution context
         */
        virtual void updateExecutionContext(long, CFGIExecutionContext *) = 0;

        /**
         * remove execution context from list
         *
         * @param id                    serial number in the list of Execution Contexts
         */
        virtual void removeExecutionContext(long) = 0;

        /**
         * count managed configurations
         *
         * @return int
         */
        virtual long countManagedConfigurations() = 0;

        /**
         * get managed configuration
         *
         * @param id                    serial number in the list of Managed configurations
         * @return CFGIConfiguration or null
         */
        virtual CFGIConfiguration *getManagedConfiguration(long) = 0;

        /**
         * insert configuration in list
         * Shifts the element currently at that position (if any) and any subsequent elements to the right (adds one to their indices).
         *
         * @param id                    serial number in the list of Managed configurations
         * @param configuration         configuration
         */
        virtual void insertManagedConfiguration(long, CFGIConfiguration *) = 0;

        /**
         * update configuration in list
         *
         * @param id            serial number in the list of Managed configurations
         * @param configuration configuration
         */
        virtual void updateManagedConfiguration(long, CFGIConfiguration *) = 0;

        /**
         * remove configuration from list
         *
         * @param id                    serial number in the list of Managed configurations
         */
        virtual void removeManagedConfiguration(long) = 0;

        /**
         * change type
         *
         * @param type type name or empty for default/any type (if exist)
         */
        virtual void setType(std::wstring &) = 0;

    };

    /**
     * Interface for Source filter
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGISourceFilter {
    public:
        /**
         * get type.
         *
         * @return SourceFilterType
         */
        virtual SourceFilterType getType() = 0;

        /**
         * count params
         *
         * @return int
         */
        virtual long countParams() = 0;

        /**
         * get param
         * params may have any types, depends on the SourceFilterType and id
         *
         * @param id serial number in the list of filter params
         * @return Object depend on type:
         * SFT_POSITION: std::vector<std::unique_ptr<long>>* (n*2 elements: from - inclusive and to - exclusive for range or position and nullptr), long* (period length, if greater than zero, then defines the set within which the previous list values apply), long* (count periods, determines the number of periods), long* (start offset, before the first period)
         * SFT_NUMBER: double* (min, inclusive), double* (max, inclusive)
         * SFT_STRING_EQUAL: boolean* (type, if true then need equals, also, not equal), std::wstring* (value for compare)
         * SFT_STRING_CONTAIN: boolean* (type, if true then need contain, also, not contain), std::wstring* (value)
         */
        virtual void *getParam(long) = 0;

    };

    /**
     * Interface for Source
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGISource {
    public:
        /**
         * get type of source.
         *
         * @return ContextSourceType
         */
        virtual SourceType getType() = 0;

        /**
         * count params
         *
         * @return int
         */
        virtual long countParams() = 0;

        /**
         * get param
         * params may have any types, depends on the SourceType and id
         *
         * @param id serial number in the list of source params
         * @return Object depend on type:
         * ST_MODULE_CONFIGURATION: CFGIConfiguration* configuration (source), SourceGetType* getType (type of get commands from source), long* countLast (only for ContextSourceGetType.SGT_LAST. minimum 1), bool* eventDriven (is event driven)
         * ST_EXECUTION_CONTEXT: CFGIExecutionContext* executionContext (source), SourceGetType* getType (type of get commands from source), long* countLast (only for ContextSourceGetType.SGT_LAST. minimum 1), bool* eventDriven (is event driven)
         * ST_STATIC_VALUE: IValue* (String, Number or byte array)
         * ST_MULTIPART: null
         * ST_CALLER_RELATIVE_NAME: string (caller level cfg name)
         */
        virtual void *getParam(long) = 0;

        /**
         * count filters
         *
         * @return int
         */
        virtual long countFilters() = 0;

        /**
         * get filter
         *
         * @param id serial number in the list of Filters
         * @return CFGISourceFilter or null
         */
        virtual CFGISourceFilter *getFilter(long) = 0;

    };

    /**
     * Interface for Managed Source multipart
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC CFGISourceManaged : virtual public CFGISource {
    public:
        /**
         * Create position filter and bind it to this source
         * add filter to end of current list (order = max_order + 1)
         * only for ST_MODULE_CONFIGURATION and ST_EXECUTION_CONTEXT SourceType
         *
         * @param range        n*2 elements: from - inclusive and to - exclusive for range or position and null
         * @param period       period length, if greater than zero, then defines the set within which the previous list values apply
         * @param countPeriods determines the number of periods
         * @param startOffset  before the first period
         * @return CFGISourceFilter
         */
        virtual CFGISourceFilter *createFilter(std::vector <std::unique_ptr<long>> *, long, long, long) = 0;

        /**
         * Create number filter and bind it to this source
         * add filter to end of current list (order = max_order + 1)
         * only for ST_MODULE_CONFIGURATION and ST_EXECUTION_CONTEXT SourceType
         *
         * @param fieldName  field name in ObjectArray. if empty used for simple values, overwise for ObjectArrays.
         * @param min inclusive
         * @param max inclusive
         * @return CFGISourceFilter
         */
        virtual CFGISourceFilter *createFilter(std::wstring &, double, double) = 0;

        /**
         * Create string equal filter and bind it to this source
         * add filter to end of current list (order = max_order + 1)
         * only for ST_MODULE_CONFIGURATION and ST_EXECUTION_CONTEXT SourceType
         *
         * @param fieldName  field name in ObjectArray. if empty used for simple values, overwise for ObjectArrays.
         * @param needEquals if true then need equals, also, not equal
         * @param value      value for compare
         * @return CFGISourceFilter
         */
        virtual CFGISourceFilter *createFilterStrEq(std::wstring &, bool, std::wstring &) = 0;

        /**
         * Create string contain filter and bind it to this source
         * add filter to end of current list (order = max_order + 1)
         * only for ST_MODULE_CONFIGURATION and ST_EXECUTION_CONTEXT SourceType
         *
         * @param fieldName  field name in ObjectArray. if empty used for simple values, overwise for ObjectArrays.
         * @param needContain if true then need contain, also, not contain
         * @param value       value for compare
         * @return CFGISourceFilter
         */
        virtual CFGISourceFilter *createFilterStrContain(std::wstring &, bool, std::wstring &) = 0;

        /**
         * Create object paths filter and bind it to this source
         * add filter to end of current list (order = max_order + 1)
         * only for ST_MODULE_CONFIGURATION and ST_EXECUTION_CONTEXT SourceType
         *
         * @param paths object array paths. path - dot separated names.
         * @return CFGISourceFilter
         */
        virtual CFGISourceFilter *createFilterObjectPaths(std::vector <std::wstring> *) = 0;

        /**
         * Update position filter in list
         * only for MODULE_CONFIGURATION and EXECUTION_CONTEXT SourceType
         *
         * @param id           serial number in the list
         * @param forObject    if true - used for ObjectArrays, overwise for all values
         * @param range        n*2 elements: from - inclusive and to - exclusive for range. to may be null for get only 1 element
         * @param period       period length, if greater than zero, then defines the set within which the previous list values apply
         * @param countPeriods determines the number of periods
         * @param startOffset  before the first period
         * @return CFGISourceFilter
         */
        virtual CFGISourceFilter *updateFilter(long, std::vector <std::unique_ptr<long>> *, long, long, long) = 0;

        /**
         * Update number filter in list
         * only for MODULE_CONFIGURATION and EXECUTION_CONTEXT SourceType
         *
         * @param id        serial number in the list
         * @param fieldName field name in ObjectArray. if empty used for simple values, overwise for ObjectArrays.
         * @param min       inclusive
         * @param max       inclusive
         * @return ISourceFilter
         */
        virtual CFGISourceFilter *updateFilter(long, std::wstring &, double, double) = 0;

        /**
         * Update string equal filter in list
         * only for MODULE_CONFIGURATION and EXECUTION_CONTEXT SourceType
         *
         * @param id         serial number in the list
         * @param fieldName  field name in ObjectArray. if empty used for simple values, overwise for ObjectArrays.
         * @param needEquals if true then need equals, also, not equal
         * @param value      value for compare
         * @return ISourceFilter
         */
        virtual CFGISourceFilter *updateFilterStrEq(long, std::wstring &, bool, std::wstring &) = 0;

        /**
         * Update string contain filter in list
         * only for MODULE_CONFIGURATION and EXECUTION_CONTEXT SourceType
         *
         * @param id          serial number in the list
         * @param fieldName   field name in ObjectArray. if empty used for simple values, overwise for ObjectArrays.
         * @param needContain if true then need contain, also, not contain
         * @param value       value for compare
         * @return ISourceFilter
         */
        virtual CFGISourceFilter *updateFilterStrContain(long, std::wstring &, bool, std::wstring &) = 0;

        /**
         * Update object paths filter in list
         * only for MODULE_CONFIGURATION and EXECUTION_CONTEXT SourceType
         *
         * @param id    serial number in the list
         * @param paths object array paths. path - dot separated names.
         * @return ISourceFilter
         */
        virtual CFGISourceFilter *updateFilterObjectPaths(long, std::vector <std::wstring> *) = 0;

        /**
         * remove filter from list
         *
         * @param id serial number in the list of filters
         */
        virtual void removeFilter(long) = 0;

    };

    /**
 * tool for work with unmodifiable files
 *
 * @version 1.0.0
 */
    class CLASS_DECLSPEC IFileTool {
    public:
        /**
         * get name
         *
         * @return
         */
        virtual std::wstring getName() = 0;

        /**
         * is file exist
         *
         * @return true if exist
         */
        virtual bool exists() = 0;

        /**
         * is directory
         *
         * @return true if directory
         */
        virtual bool isDirectory() = 0;

        /**
         * get files in folder
         *
         * @return files if it folder
         */
        virtual std::vector<IFileTool *> *getChildrens() = 0;

        /**
         * reed all file
         *
         * @return InputStream
         */
        virtual char *getData() = 0;

        /**
         * file size
         *
         * @return size_t
         */
        virtual size_t length() = 0;

        /**
         * treats the file as a dynamic library and tries to load it
         * if load success, return platform specific handler to library (for Windows - HMODULE) or return NULL
         *
         * @return handler or null
         */
        virtual void *loadAsLibrary() = 0;

//    virtual ~IFileTool() {};
    };

    /**
     * main configuration tool
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IConfigurationTool {
    public:
        /**
         * change variable
         *
         * @param key                   variable name
         * @param value                 value object (String, Number, byte[])
         */
        virtual void setVariable(const std::wstring &, IValue *) = 0;

        /**
         * check is variable has changed from last execution or last check
         * usfull for check changes from external (processes or user)
         *
         * @param key                   variable name
         * @return
         */
        virtual bool isVariableChanged(const std::wstring &) = 0;

        /**
         * remove variable
         *
         * @param key                   variable name
         * @return
         */
        virtual void removeVariable(const std::wstring &) = 0;

        /**
         * get module folder
         * contains all files, what was in smcm file.
         *
         * @return
         */
        virtual IFileTool *getHomeFolder() = 0;

        /**
         * get full path to work directory
         * only if module allow this
         *
         * @return
         * @throws ModuleException if module not allow work with work directory
         */
        virtual std::wstring getWorkDirectory() = 0;

        /**
         * count configuration execution contexts
         *
         * @return int
         */
        virtual long countExecutionContexts() = 0;

        /**
         * get execution context
         *
         * @param id                    serial number in the list of Execution Contexts
         * @return CFGIExecutionContext or null
         */
        virtual CFGIExecutionContext *getExecutionContext(long) = 0;

        /**
         * get configuration related to this launch
         * @return CFGIConfiguration
         */
        virtual CFGIConfiguration *getConfiguration() = 0;

        /**
         * get container

         * @return CFGIContainerManaged
         */
        virtual CFGIContainerManaged *getContainer() = 0;

        /**
         * logger trace
         *
         * @param text - text
         */
        virtual void loggerTrace(std::wstring &) = 0;

        /**
         * logger debug
         *
         * @param text - text
         */
        virtual void loggerDebug(std::wstring &) = 0;

        /**
         * logger info
         *
         * @param text - text
         */
        virtual void loggerInfo(std::wstring &) = 0;

        /**
         * logger warn
         *
         * @param text - text
         */
        virtual void loggerWarn(std::wstring &) = 0;

        /**
         * logger error
         *
         * @param text - text
         */
        virtual void loggerError(std::wstring &) = 0;

        /**
         * get info by name
         *
         * @param key name
         * @return IValue or null
         */
        virtual IValue *getInfo(const std::wstring &) = 0;

//    virtual ~IConfigurationTool() {};
    };

    /**
     * Tool for work with managed configurations
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IConfigurationControlTool {
    public:
        /**
         * count managed configurations
         *
         * @return
         */
        virtual long countModules() = 0;

        /**
         * get module
         *
         * @return CFGIModule or null
         */
        virtual CFGIModule *getModule(long) = 0;

        /**
         * count managed configurations
         *
         * @return
         */
        virtual long countManagedConfigurations() = 0;

        /**
         * get managed configuration
         *
         * @param id                    serial number in the list of Managed configurations
         * @return CFGIConfigurationManaged or null
         */
        virtual CFGIConfigurationManaged *getManagedConfiguration(long) = 0;

        /**
         * create configuration and add it in list of managed configurations
         *
         * @param id                    index at which the specified element is to be inserted
         * @param container             container
         * @param module                module
         * @param name                  unique name for configuration
         * @return CFGIConfigurationManaged
         */
        virtual CFGIConfigurationManaged *createConfiguration(long, CFGIContainer *, CFGIModule *, const std::wstring &) = 0;

        /**
         * remove managed configuration
         *
         * @param id                    serial number in the list of Managed configurations
         */
        virtual void removeManagedConfiguration(long) = 0;

        /**
         * delete all dynamically created cfg objects.
         * in the end of execution called automatically.
         */
        virtual void clearCache() = 0;

    };

    /**
     * Tool for throw new command to managed execution contexts and get result
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IFlowControlTool {
    public:
        /**
         * count managed execution contexts
         *
         * @return
         */
        virtual long countManagedExecutionContexts() = 0;

        /**
         * throw new command to managed execution context
         * command execute in this thread
         * function will wait for the command to execute
         *
         * @param type
         * @param managedId             serial number in the list of Managed execution contexts
         * @param values                list of values for create dummy messages from this process, or null
         */
        virtual void executeNow(CommandType, long, std::vector<IValue *> *) = 0;

        /**
         * throw new command to managed execution context
         * command execute in new thread
         * function return control immediately
         *
         * @param type
         * @param managedIds            serial number in the list of Managed execution contexts
         * @param values                list of values for create dummy messages from this process, or null
         * @param waitingTacts          if it is necessary that the new thread first wait for the specified time (in tacts)
         * @param maxWorkInterval       define max work interval of new thread (in tacts)
         * @return return id of thread
         */
        virtual long long int executeParallel(CommandType, long, std::vector<IValue *> *, long, long) = 0;

//    virtual bool isExecute(long) = 0;

        /**
         * check is thread alive
         *
         * @param threadId              id thread
         * @return
         */
        virtual bool isThreadActive(long long int) = 0;

        /**
         * get data from managed execution context
         * who receive commands from this process
         *
         * @param managedId             serial number in the list of Managed execution contexts
         * @return only DATA messages
         */
        virtual std::vector<IAction *> *getMessagesFromExecuted(long) = 0;

        /**
         * get data from managed execution context
         * who receive commands from this process
         * in parallel thread
         *
         * @param threadId              id thread
         * @param managedId             serial number in the list of Managed execution contexts
         * @return only DATA messages
         */
        virtual std::vector<IAction *> *getMessagesFromExecuted(long long int, long) = 0;

        /**
         * work as getMessagesFromExecuted
         *
         * @param managedId
         * @return commands
         */
        virtual std::vector<ICommand *> *getCommandsFromExecuted(long) = 0;

        /**
         * work as getMessagesFromExecuted
         *
         * @param threadId
         * @param managedId
         * @return commands
         */
        virtual std::vector<ICommand *> *getCommandsFromExecuted(long long int, long) = 0;

        /**
         * after executeParallel and work with him, need to release thread
         *
         * @param threadId id thread
         */
        virtual void releaseThread(long long int) = 0;

        /**
         * after executeParallel and work with him, need to release thread
         * if thread work - not stop it
         *
         * @param threadId id thread
         */
        virtual void releaseThreadCache(long long int) = 0;

//    virtual bool isError(long) = 0;

//    virtual bool isProcessReady(long) = 0;

//    virtual bool isProcessExist(long) = 0;

//    virtual ~IFlowControlTool() {};

        /**
         * get managed execution context
         *
         * @param id serial number in the list of Managed execution contexts
         * @return CFGIExecutionContext or null
         */
        virtual CFGIExecutionContext *getManagedExecutionContext(int id) = 0;

    };

    /**
    * main execution context tool
    *
    * @version 1.0.0
    */
    class CLASS_DECLSPEC IExecutionContextTool {
    public:
        /**
        * emit message
        * type DATA
        *
        * @param value                  object (type String, Number, byte[])
        */
        virtual void addMessage(IValue *) = 0;

        /**
         * emit error message
         * type ERROR
         *
         * @param value                 object (type String, Number, byte[])
         */
        virtual void addError(IValue *) = 0;

        /**
         * emit log message
         * type LOG
         *
         * @param value object
         */
        virtual void addLog(std::wstring &) = 0;

        /**
         * get count commands in source
         *
         * @param sourceId              serial number in the list of Sources
         * @return count
         */
        virtual long countCommands(long) = 0;

        /**
         * get count commands (all) for managed execution context
         *
         * @param executionContext      managed execution context
         * @return count
         */
        virtual long countCommands(CFGIExecutionContextManaged *) = 0;

        /**
         * get Process Actions from source
         *
         * @param sourceId              serial number in the list of Sources
         * @return only DATA messages
         */
        virtual std::vector<IAction *> *getMessages(long) = 0;

        /**
         * get Process Actions from source
         * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
         *
         * @param sourceId              serial number in the list of Sources
         * @param fromIndex             start serial number in the list of commands in source (exclusive)
         * @param toIndex               end serial number in the list of commands in source (inclusive)
         * @return only DATA messages
         */
        virtual std::vector<IAction *> *getMessages(long, long, long) = 0;

        /**
         * get Commands from source
         *
         * @param sourceId              serial number in the list of Sources
         * @return commands
         */
        virtual std::vector<ICommand *> *getCommands(long) = 0;

        /**
         * get Commands from source
         * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
         *
         * @param sourceId              serial number in the list of Sources
         * @param fromIndex             start serial number in the list of commands in source
         * @param toIndex               end serial number in the list of commands in source
         * @return commands
         */
        virtual std::vector<ICommand *> *getCommands(long, long, long) = 0;

        /**
         * get Commands from managed execution context
         * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
         *
         * @param executionContext      managed execution context
         * @param fromIndex             start serial number in the list of commands in source
         * @param toIndex               end serial number in the list of commands in source
         * @return commands
         */
        virtual std::vector<ICommand *> *getCommands(CFGIExecutionContextManaged *, long, long) = 0;

        /**
         * is Process Actions has errors
         *
         * @param action
         * @return
         */
        virtual bool isError(IAction *action) = 0;

        /**
         * get tool for work with managed configurations
         *
         * @return
         */
        virtual IConfigurationControlTool *getConfigurationControlTool() = 0;

        /**
         * get tool for throw new command to managed execution contexts and get result
         *
         * @return
         */
        virtual IFlowControlTool *getFlowControlTool() = 0;

        /**
         * check is need stop process work immediately
         * usefull for long work (example - web server)
         *
         * @return
         */
        virtual bool isNeedStop() = 0;

        /**
         * get execution context related to this launch
         * @return CFGIExecutionContext
         */
        virtual CFGIExecutionContext *getExecutionContext() = 0;

//    virtual ~IExecutionContextTool() {};
    };

    /**
     * Main module interface
     *
     * @version 1.0.0
     */
    class CLASS_DECLSPEC IMethod {
    public:
        /**
         * call once per process on start
         *
         * @param                       configurationTool
         * @throws ModuleException
         */
        virtual void start(IConfigurationTool *, IValueFactory *) = 0;

        /**
         * main method. call every time when need execute
         *
         * @param                       configurationTool
         * @param                       executionContextTool
         * @throws ModuleException
         */
        virtual void process(IConfigurationTool *, IExecutionContextTool *, IValueFactory *) = 0;

        /**
         * call then need update
         *
         * @param                       configurationTool
         * @throws ModuleException
         */
        virtual void update(IConfigurationTool *, IValueFactory *) = 0;

        /**
         * call once per process on stop
         *
         * @param                       configurationTool
         * @throws ModuleException
         */
        virtual void stop(IConfigurationTool *, IValueFactory *) = 0;
    };

}

#endif //SMCMODULEDEFINITIONPROVIDER_SMCAPI_H

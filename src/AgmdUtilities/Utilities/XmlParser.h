#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include <Utilities/SmartPtr.h>
#include <Utilities/Singleton.h>

#include <string>
#include <sstream>
#include <map>
#include <vector>

namespace AgmdUtilities
{
    using namespace std;


    enum NodeType
    {
        NODE_BALISE,
        NODE_TXT
    };

    typedef map<std::string,std::string> Argument;
    class XmlNode;
    typedef SmartPtr<XmlNode> XmlNodePtr;
    class XmlNode
    {
    public:
        typedef vector<XmlNodePtr> XmlNodeVector;
        XmlNode(NodeType type);

        XmlNodePtr GetChild(NodeType type);
        XmlNodePtr GetChild(string name);
        XmlNodePtr* GetChilds();
        NodeType GetType();

        virtual string ToSTring() = 0;

        virtual Argument GetArgs();
        virtual string GetTxT();
        virtual string GetName() = 0;
        void AddChild(XmlNodePtr node);
    private:
        virtual void SetArgs(Argument args);
        NodeType m_type;
    protected:
        XmlNodeVector m_childnode;

    };

    class XmlBaliseNode : public XmlNode
    {
    public:
        XmlBaliseNode();
        XmlBaliseNode(string name);
        XmlBaliseNode(string name, Argument args);
        virtual Argument GetArgs();
        virtual string GetName();
        virtual string ToSTring();
    private:
        virtual void SetArgs(Argument);
        Argument m_args;
        string m_name;
    };

    class XmlTxtNode : public XmlNode
    {
    public:
        XmlTxtNode();
        XmlTxtNode(string str);
        virtual string GetTxT();
        virtual string GetName();
        virtual string ToSTring();
    private:
        string m_txt;
    };

    class XmlParser : public Singleton<XmlParser>
    {
    MAKE_SINGLETON(XmlParser);
    public:
        friend class XmlNode;
        XmlNodePtr Parse(string str);

    private:
        XmlParser();
        ~XmlParser();
        enum BaliseType 
        {
            BALISENAME_SHADERPIPELINE,
            BALISENAME_SUBSHADER,
            BALISENAME_PASS
        };
        enum ElementType
        {
            ELEMENT_BALISE_BEGIN,
            ELEMENT_BALISE_END,
            ELEMENT_BALISE_AUTOCLOSE,
            ELEMENT_TXT,
            ELEMENT_UNKNOWN
        };
        struct Element
        {
            ElementType _type;
            Argument args;
            string str;
            string name;
        };
        Element GetElement(std::stringstream& stream);
        void GetNextArg(stringstream& stream, string& arg, string& value);
        const char* skipWhiteSpace(const char* c);
        bool isWhiteSpace(const char* c);
    };

}


#endif /* _XMLPARSER_H_ */

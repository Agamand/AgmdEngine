/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Utilities/XmlParser.h>
#include <CommonDefines.h>

#include <stack>

SINGLETON_IMPL(AgmdUtilities::XmlParser);
namespace AgmdUtilities
{

    XmlNode::XmlNode(NodeType type) :
    m_type(type)
    {}

    XmlNodePtr XmlNode::GetChild(NodeType type)
    {
        size_t size = m_childnode.size();
        for(size_t i = 0; i < size; i++)
        {
            if(m_childnode[i]->GetType() == type)
                return m_childnode[i];
        }
        return NULL;
    }

    XmlNodePtr XmlNode::GetChild(string name)
    {
        size_t size = m_childnode.size();
        for(size_t i = 0; i < size; i++)
        {
            if(m_childnode[i]->GetName() == name)
                return m_childnode[i];
        }
        return NULL;
    }

    XmlNodePtr* XmlNode::GetChilds()
    {
        return m_childnode.size() > 0 ? &m_childnode[0] : NULL;
    }

    void XmlNode::AddChild(XmlNodePtr node)
    {
        m_childnode.push_back(node);
    }

    NodeType XmlNode::GetType()
    {
        return m_type;
    }

    string XmlNode::GetTxT()
    {
        return "";
    }

    void XmlNode::SetArgs(Argument args)
    {}

    Argument XmlNode::GetArgs()
    {
        return Argument();
    }

    XmlBaliseNode::XmlBaliseNode() :
    XmlNode(NODE_BALISE)
    {}

    XmlBaliseNode::XmlBaliseNode(string name, Argument args) : 
    XmlNode(NODE_BALISE),
    m_name(name),
    m_args(args)
    {}

    XmlBaliseNode::XmlBaliseNode(string name) : 
    XmlNode(NODE_BALISE),
    m_name(name)
    {}

    Argument XmlBaliseNode::GetArgs()
    {
        return m_args;
    }

    string XmlBaliseNode::GetName()
    {
        return m_name;
    }

    void XmlBaliseNode::SetArgs(Argument args)
    {
        m_args = args;
    }

    string XmlBaliseNode::ToSTring()
    {
        string str = "";
        str +="<";
        str += m_name;
        for(Argument::iterator itr = m_args.begin(); itr != m_args.end(); itr++)
        {
            str+=" " + itr->first + " = " + itr->second;
        }
        if(!m_childnode.size())
        {
            str += "/>";
            return str;
        }
        str +=">";
        for(uint32 i = 0; i < m_childnode.size(); i++)
            str += m_childnode[i]->ToSTring();
        str +="</";
        str += m_name;
        str += ">";
        return str;
    }

    XmlTxtNode::XmlTxtNode() :
    XmlNode(NODE_TXT)
    {}

    XmlTxtNode::XmlTxtNode(string str) :
    XmlNode(NODE_TXT),
    m_txt(str)
    {}

    string XmlTxtNode::GetName()
    {
        return "txt";
    }

    string XmlTxtNode::GetTxT()
    {
        return m_txt;
    }

    string XmlTxtNode::ToSTring()
    {
        return m_txt;
    }
    
    XmlParser::XmlParser()
    {}

    XmlParser::~XmlParser()
    {}

    XmlNodePtr XmlParser::Parse(string str)
    {
        XmlNodePtr mainNode = new XmlBaliseNode("mainNode");
        stack<XmlNodePtr> xmlStack;
        xmlStack.push(mainNode);
        stringstream stream;
        stream.setf(stringstream::eofbit | stringstream::failbit);
        stream << str;
        XmlParser::Element elt;
        elt = GetElement(stream);

        size_t size = 0;
        size = str.length();
        string strelement;
        char c;
        for(size_t i = 0; i < size; i++)
        {
            c = str.at(i);
            switch(c)
            {
            case '\t':
            case ' ':
                if(elt._type == ELEMENT_TXT)
                    strelement +=c;
                break;
            case '<':
                strelement +=c;
                break;
            case '>':
                if(elt._type == ELEMENT_BALISE_AUTOCLOSE )
                    break;
            }
        }


        while(elt._type != ELEMENT_UNKNOWN)
        {
            XmlNodePtr node;
            switch (elt._type)
            {
            case ELEMENT_BALISE_BEGIN:
                node = new XmlBaliseNode(elt.name,elt.args);
                xmlStack.top()->AddChild(node);
                xmlStack.push(node);
                break;
            case ELEMENT_BALISE_END:
                if(xmlStack.top()->GetName() == elt.name)
                    xmlStack.pop();
                break;
            case ELEMENT_BALISE_AUTOCLOSE:
                node = new XmlBaliseNode(elt.name,elt.args);
                xmlStack.top()->AddChild(node);
                break;
            case ELEMENT_TXT:
                node = new XmlTxtNode(elt.str);
                xmlStack.top()->AddChild(node);
                break;
            }
            elt = GetElement(stream);
        }
        return mainNode;
    }

    #define IS_SPACER(a) (a == ' ' || a == '\t')

    XmlParser::Element XmlParser::GetElement(stringstream& stream)
    {
        char c;
        std:: string str;
        Element elt;
        if(stream.read(&c,1) != stream)
              return elt;
        //stream >> c;
        elt._type = ELEMENT_UNKNOWN;
        try
        {
            if(c == '<')
            {
                elt._type = ELEMENT_BALISE_BEGIN;
                if(stream.read(&c,1) != stream)
                        return elt;
                while(IS_SPACER(c))
                    if(stream.read(&c,1) != stream)
                        return elt;

                if(c == '/')
                {
                    elt._type = ELEMENT_BALISE_END;
                    if(stream.read(&c,1) != stream)
                        return elt;
                }
            
               // stream.read(&c,1);
                while(c != '>')
                {
                    if(!IS_SPACER(c))
                        str +=c;

                    if(IS_SPACER(c) && str.length())
                        break;
                    if(stream.read(&c,1) != stream)
                        return elt;
                }
                elt.name = str;
                str = "";

                // args finder
                string arg = "";
                string value = "";
                bool separatorFound = false;
                while(c != '>')
                {
                    if(c == '/' && elt._type == ELEMENT_BALISE_BEGIN)
                        elt._type = ELEMENT_BALISE_AUTOCLOSE;

                    if(elt._type == ELEMENT_BALISE_END || elt._type == ELEMENT_BALISE_AUTOCLOSE)
                    {
                        if(stream.read(&c,1) != stream)
                            return elt;
                        continue;
                    }
                    
                    if(IS_SPACER(c) || c == '=')
                    {
                        if(c == '=')
                            separatorFound = true;

                        if(!arg.length() && str.length())
                        {
                            arg = str;
                            str = "";
                        }
                        else if(!value.length() && str.length() && separatorFound && arg.length())
                        {
                            value = str;
                            str = "";
                            elt.args[arg] = value;
                            separatorFound = false;
                            arg = "";
                            value = "";
                        }
                        if(stream.read(&c,1) != stream)
                            return elt;
                        continue;
                    }

                    if(arg.length() && !IS_SPACER(c) && !separatorFound)
                    {
                       elt.args[arg] = "true";
                       separatorFound = false;
                       arg ="";
                    }

                    str+=c;
                    if(stream.read(&c,1) != stream)
                        return elt;
                }

                if(arg.length())
                {
                    elt.args[arg] = str.length() ? str : "true";
                    arg = "";
                    str = "";
                }

            }else
            {
                elt._type = ELEMENT_TXT;
                char c;
                if(stream.read(&c,1) != stream)
                    return elt;
                while(c != '<')
                {
                    str +=c;
                    if(stream.read(&c,1) != stream)
                        return elt;
                }
                stream.seekg(-1,ios_base::cur);
                elt.str = str;
            }
        }catch (exception e)
        {
               //
        }
        return elt;
    }
    
    /** useless function **/
    void GetNextArg(stringstream& stream, string& arg, string& value)
    {}

    const char* XmlParser::skipWhiteSpace(const char* c)
    {
        if(!c || !*c)
            return NULL;

        while(!c || !*c)
        {
            if(!isWhiteSpace(c))
                return c;
            c++;
        }
        return 0;
    }

    bool XmlParser::isWhiteSpace(const char* c)
    {
        return isspace(*c) || *c == '\n' || *c == '\r';
    }

}
#include "FunctionInfo.h"


void FunctionInfo::set(const FunctionInfo &other)
{
    m_functionName = other.m_functionName,
    m_className = other.m_className,
    m_namespaces = other.m_namespaces,
    m_arguments = other.m_arguments,
    m_ante = other.m_ante,
    m_post = other.m_post,
    m_flags = other.m_flags;
}

void FunctionInfo::parse(const QString &qFileInfo)
{
    m_qFuncInfo = qFileInfo;
    splitStrings();
    parseAnte();
    parseNames();
    parseArgs();
    parsePost();
}

void FunctionInfo::splitStrings()
{

}

void FunctionInfo::parseAnte()
{

}

void FunctionInfo::parseNames()
{

}

void FunctionInfo::parseArgs()
{

}

void FunctionInfo::parsePost()
{

}

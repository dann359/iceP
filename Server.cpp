// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Chat.h>

using namespace std;
using namespace Demo;

class ChatI : public Chat
{
public:

    string printString(const string &, const Ice::Current&);
};

string 
ChatI::
printString(const string &s, const Ice::Current&)
{
    cout << s << endl;
    return s;
}

int
main(int argc, char* argv[])
{
    int status = 0;
    Ice::CommunicatorPtr ic;
    try
    {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter =
            ic->createObjectAdapterWithEndpoints("SimplePrinterAdapter", "default -h localhost -p 10000");
        Ice::ObjectPtr object = new ChatI;
        adapter->add(object, ic->stringToIdentity("SimplePrinter"));
        adapter->activate();
        ic->waitForShutdown();
    }
    catch(const Ice::Exception& e)
    {
        cerr << e << endl;
        status = 1;
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
        status = 1;
    }
    if(ic)
    {
        try
        {
            ic->destroy();
        }
        catch(const Ice::Exception& e)
        {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}


#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/MasterRegistrar.hpp"


using namespace BitProfile;


int main(int argc, char **argv)
{

    Ethereum::Connector::Provider provider;
    provider.connect();

    MasterRegistrar master(provider, BitProfile::Test_Net);
    MasterRegistrar::URIList list = master.getURIList();

    std::cout<<"registrars : "<<std::endl;
    for(MasterRegistrar::URIList::Iterator it = list.begin(), end = list.end(); it!=end; ++it)
    {
        std::cout<<"* "<<it->toString();
        Registrar registrar = master.get(it->getIndex());
        std::cout<<" : "<<registrar.getAddress()<<std::endl;
    }

    std::cout<<std::endl;

    return 0;
}


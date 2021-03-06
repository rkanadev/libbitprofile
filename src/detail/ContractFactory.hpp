#pragma once


#include "ContractCode.hpp"
#include "types.hpp"


namespace BitProfile{


using Ethereum::Connector::Provider;


template<class Contract>
class ContractFactory : public Ethereum::Connector::ContractFactory
{
    public:
        typedef Ethereum::Connector::ContractFactory Base;
        typedef Ethereum::Connector::Contract BaseContract;

    public:

        ContractFactory(Provider &,  const std::string &code);

        Contract at(const address_t &address);

        Contract deploy(const std::string &password);
        Contract deploy(const arguments_t &, const std::string &password);

        template<class CallBack>
        void deploy(const std::string &password, const CallBack &);

        template<class CallBack>
        void deploy(const arguments_t &, const std::string &password, const CallBack &);

    private:
        Contract cast(const BaseContract &);

        using Base::deploy;
        using Base::at;

    private:
        template<class CallBack>
        class CallBackWrapper
        {
            public:
                CallBackWrapper(const CallBack &, ContractFactory<Contract> &);

                void operator()(const boost::system::error_code &);
                void operator()(const BaseContract &);

            private:
                CallBack _callback;
                ContractFactory<Contract> &_factory;
        };

    private:
        Provider &_provider;
        const std::string &_code;
};




#define DECLARE_CONTRACT_FACTORY(ClassName, ContractName, ContractCode)       \
class ClassName : public ContractFactory<ContractName>                        \
{                                                                             \
    public:                                                                   \
        typedef ContractFactory<ContractName> Base;                           \
                                                                              \
    public:                                                                   \
        inline ClassName(Provider &provider) : Base(provider, ContractCode)   \
        {}                                                                    \
}


}

#include "ContractFactory.ipp"

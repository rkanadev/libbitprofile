#pragma once 


#include <ostream>
#include <istream>
#include <json/value.h>
#include <json/writer.h>
#include <json/reader.h>


#include "Profile.hpp"
#include "AddressAuthKey.hpp"
#include "detail/KeyAdapter.hpp"
#include "detail/KeyTypeName.hpp"
#include "AddressAuthKey.hpp"


namespace BitProfile{


class ProfileAdministrator;

class ProfileDescriptor
{
    public:

        ProfileDescriptor();

        template<class Key>
        ProfileDescriptor(const Profile &, const Key &);

        ProfileDescriptor(const ProfileAdministrator &);
        ProfileDescriptor(const Json::Value &);

        void setURI(const Profile::URI &);
        void reset(const Json::Value &);

        std::string getURI() const;
        std::string getName() const;
        std::string getContext() const;
        address_t getAddress() const;

        std::string getAuthType() const;
        std::string getAuthAddress() const;

        KeyAdapter getProfileKey() const;

        const Json::Value & toJSON() const;

    private:
        void parseProfileData(const Profile &);
        void parseKeyData(const Profile &, const AddressAuthKey &);

        template<class Key>
        void parseKeyData(const Profile &profile, const Key &key, const std::string &keyType);

    private:
        Json::Value _data;
};


}


std::ostream & operator << (std::ostream &, const BitProfile::ProfileDescriptor &);
std::istream & operator >> (std::istream &, BitProfile::ProfileDescriptor &);

#include "ProfileDescriptor.ipp"

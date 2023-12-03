#ifndef MY_EXCEPTIONS_HPP
#define MY_EXCEPTIONS_HPP

#include <stdexcept>
#include <exception>

namespace se{

class InValidSrcURL : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class LaodJsonError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class CommunicationError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class InValidArg : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

class StorageError : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

class SearchError : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

class CreateSocketError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};

class BindingSocketError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};

class ListenError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};

class AcceptError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};

class ReadError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};

class WriteError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};

class FileDiscreptorError : public se::CommunicationError
{
public:
    using se::CommunicationError::CommunicationError;
};



}//namespace es

#endif
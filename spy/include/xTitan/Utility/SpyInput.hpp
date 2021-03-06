/*
Copyright (c) 2011 NCU OOlab <ncuoolab@gmail.com>
*/
#ifndef XTITAN_SPY_SPYINPUT_HPP
#define XTITAN_SPY_SPYINPUT_HPP

#include <memory>
#include <string>

#include "xTitan/Utility/SpyConfig.hpp"


namespace xtitan {
namespace detail {

class XTITAN_SPY_DLL SpyInput {
public:
	SpyInput( const char * objectName, const char * signature );
	~SpyInput();

	SpyInput & operator %( bool b );
	SpyInput & operator %( int i );
	SpyInput & operator %( double d );
	SpyInput & operator %( const char * s );
	SpyInput & operator %( const std::string & s );
	SpyInput & operator %( const wchar_t * ws );
	SpyInput & operator %( const std::wstring & ws );

private:
	SpyInput( const SpyInput & );
	SpyInput & operator =( const SpyInput & );

	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

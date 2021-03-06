/*
Copyright (c) 2011 NCU OOlab <ncuoolab@gmail.com>
*/
#include "Logger_p.hpp"

#include <QtCore/QDateTime>
#include <QtCore/QMutexLocker>
#include <QtCore/QTextCodec>

#include "xTitan/Exception/InternalError.hpp"
#include "xTitan/Exception/IOError.hpp"
#include "xTitan/Utility/Setting.hpp"


using xtitan::Logger;
using xtitan::Setting;


std::shared_ptr< Logger > Logger::Private::self;

void Logger::Private::destroy( Logger * self ) {
	delete self;
}

Logger::Private::Private():
lock(),
tcDir( Setting::instance().get( "TestCasePath" ).toString() ),
fout( this->tcDir.filePath( QDateTime::currentDateTime().toString( "yyyyMMdd_hhmmss" ) + ".log" ) ),
stream() {
	if( !this->fout.isOpen() ) {
		bool result = this->fout.open( QIODevice::WriteOnly | QIODevice::Text );
		if( !result ) {
			throw IOError( "Can not open log file" );
		}
	}
	this->stream.setDevice( &this->fout );
	this->stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );
}

void Logger::initialize() {
	if( Private::self ) {
		return;
	}
	Private::self.reset( new Logger, Private::destroy );
}

/**
 * @warning This function is NOT thread-safe
 */
Logger & Logger::instance() {
	if( !Private::self ) {
		throw InternalError( "xtitan::Logger does not initialized yet" );
	}
	return *Private::self;
}

Logger::Logger():
p_( new Private ) {
}

Logger::~Logger() {
	qint64 fsize = this->p_->fout.size();
	this->p_->fout.close();
	if( fsize == 0L ) {
		this->p_->fout.remove();
	}
}

void Logger::setFileName( const QString & name ) {
	QMutexLocker locker( &this->p_->lock );

	this->p_->fout.close();
	this->p_->fout.setFileName( this->p_->tcDir.filePath( name ) );

	if( !this->p_->fout.isOpen() ) {
		bool result = this->p_->fout.open( QIODevice::WriteOnly | QIODevice::Text );
		if( !result ) {
			throw IOError( "Can not open log file" );
		}
	}
	this->p_->stream.setDevice( &this->p_->fout );
	this->p_->stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

	locker.unlock();
}

void Logger::log( const QString & msg ) {
	QMutexLocker locker( &this->p_->lock );

	this->p_->stream << msg << "\n";
	this->p_->stream.flush();

	locker.unlock();
}

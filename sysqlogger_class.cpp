/* LICENSE TEXT

    audioplayer for linux based using RtAudio and RtMidi libraries to
    process audio and receive MTC sync. It also uses oscpack to receive
    some configurations through osc commands.
    Copyright (C) 2020  Stage Lab & bTactic.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Stage Lab SysQ logger class source file
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#include "sysqlogger_class.h"

// Static class members initialize
SysQLogger* SysQLogger::myObjectPointer = NULL;
std::string SysQLogger::programSlug;

//////////////////////////////////////////////////////////
SysQLogger::SysQLogger ( const string slug )
{
    // Reinitialize our static log file data
    // logPath = file;
    programSlug = "SysQ:" + slug;

    // Open the file to append text
    // logFile.open( logPath.string(), ios::app );
    openlog( programSlug.c_str(), LOG_CONS | LOG_PID | LOG_NDELAY , LOG_LOCAL0 );

    myObjectPointer = this;
}

//////////////////////////////////////////////////////////
SysQLogger::~SysQLogger (void)
{
    logInfo("Log finished");

    closelog();
}

//////////////////////////////////////////////////////////
SysQLogger* SysQLogger::getLogger( void ) {
    if (myObjectPointer == NULL){
        myObjectPointer = new SysQLogger();
    }
    return myObjectPointer;
}

//////////////////////////////////////////////////////////
void SysQLogger::logEmergency(const string& message)
{
    syslog( LOG_EMERG, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logAlert(const string& message)
{
    syslog( LOG_ALERT, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logCritical(const string& message)
{
    syslog( LOG_CRIT, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logError(const string& message)
{
    syslog( LOG_ERR, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logWarning(const string& message)
{
    syslog( LOG_WARNING, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logNotice(const string& message)
{
    syslog( LOG_NOTICE, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logInfo(const string& message)
{
    syslog( LOG_INFO, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logDebug(const string& message)
{
    syslog( LOG_DEBUG, "%s", message.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::logOK(const string& message)
{
    string str = "[OK] " + message;
    syslog( LOG_INFO, "%s", str.c_str() );
}

//////////////////////////////////////////////////////////
void SysQLogger::setNewSlug(const string newSlug) {
    string str = "Changed program slug from " + programSlug + " to " + newSlug;

    logInfo( str.c_str() );

    programSlug = "SysQ:" + newSlug;
}

//////////////////////////////////////////////////////////
string  SysQLogger::getSlug( void ) {
    return programSlug;
}


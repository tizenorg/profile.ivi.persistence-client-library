#ifndef PERSISTENCE_CLIENT_LIBRARY_DBUS_SERVICE_H_
#define PERSISTENCE_CLIENT_LIBRARY_DBUS_SERVICE_H_

/******************************************************************************
 * Project         Persistency
 * (c) copyright   2012
 * Company         XS Embedded GmbH
 *****************************************************************************/
/******************************************************************************
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a  copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
******************************************************************************/
 /**
 * @file           persistence_client_library_dbus_service.h
 * @ingroup        Persistence client library
 * @author         Ingo Huerner
 * @brief          Header of the persistence client library dbus service.
 * @see
 */

#include <dbus/dbus.h>
#include <poll.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>

#include "persistence_client_library_data_organization.h"

/// command definitions for main loop
typedef enum ECmd
{
	/// command none
   CMD_NONE = 0,
   /// command block access and write data back
   CMD_PAS_BLOCK_AND_WRITE_BACK,
   /// command to prepare shutdown
   CMD_LC_PREPARE_SHUTDOWN,
   /// command send changed notification signal
   CMD_SEND_NOTIFY_SIGNAL,
   /// command send register/unregister command
   CMD_REG_NOTIFY_SIGNAL,
   /// command send admin register/unregister
   CMD_SEND_PAS_REGISTER,
   /// command send lifecycle register/unregister
   CMD_SEND_LC_REGISTER,
   /// quit command
   CMD_QUIT
} tCmd;


/// command data union definition
typedef union MainLoopData_u_{

	/// message structure
	struct {
		/// dbus mainloop command
		uint32_t cmd;
		/// unsigned int parameters
		uint32_t params[4];
		/// string parameter
		char string[DbKeyMaxLen];
	} message;

	/// the message payload
	char payload[128];
} MainLoopData_u;


/// mutex to make sure main loop is running
extern pthread_mutex_t gDbusInitializedMtx;
/// dbus init conditional variable
extern pthread_cond_t  gDbusInitializedCond;
/// dbus pending mutex
extern pthread_mutex_t gDbusPendingRegMtx;
/// dbus mainloop conditional variable
extern pthread_mutex_t gMainCondMtx;
/// dbus mainloop mutex
extern pthread_t gMainLoopThread;

/// lifecycle consumer interface dbus name
extern const char* gDbusLcConsterface;
/// lifecycle consumer dbus interface
extern const char* gDbusLcCons;
/// lifecycle consumer dbus destination
extern const char* gDbusLcConsDest;
/// lifecycle consumer dbus path
extern const char* gDbusLcConsPath;
/// lifecycle consumer debus message
extern const char* gDbusLcConsMsg;
/// lifecycle consumer dbus interface
extern const char* gDbusLcInterface;

/// persistence administrator consumer dbus interface
extern const char* gDbusPersAdminConsInterface;
/// persistence administrator consumer dbus
extern const char* gDbusPersAdminPath;
/// persistence administrator consumer dbus interface message
extern const char* gDbusPersAdminConsMsg;
/// persistence administrator dbus
extern const char* gDbusPersAdminInterface;
/// persistence administrator dbus path
extern const char* gPersAdminConsumerPath;


/**
 * @brief DBus main loop to dispatch events and dbus messages
 *
 * @param vtable the function pointer tables for '/org/genivi/persistence/adminconsumer' messages
 * @param vtable2 the function pointer tables for '/com/contiautomotive/NodeStateManager/LifecycleConsumer' messages
 * @param vtableFallback the fallback function pointer tables
 * @param userData data to pass to the main loop
 *
 * @return 0
 */
int mainLoop(DBusObjectPathVTable vtable, DBusObjectPathVTable vtable2,
             DBusObjectPathVTable vtableFallback, void* userData);


/**
 * @brief Setup the dbus main dispatching loop
 *
 * @return 0
 */
int setup_dbus_mainloop(void);


/**
 * @brief deliver message to mainloop (blocking)
 *        The function blocks until the message has
 *        been delivered to the mainloop
 *
 * @param payload the message to deliver to the mainloop (command and data)
 *
 * @return 0
 */
int deliverToMainloop(MainLoopData_u* payload);


/**
 * @brief deliver message to mainloop (non blocking)
 *        The function does N O T  block until the message has
 *        been delivered to the mainloop
 *
 * @param payload the message to deliver to the mainloop (command and data)
 *
 * @return 0
 */
int deliverToMainloop_NM(MainLoopData_u* payload);


#endif /* PERSISTENCE_CLIENT_LIBRARY_DBUS_SERVICE_H_ */

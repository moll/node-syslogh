#include <node.h>
#include <v8.h>
#include <nan.h>
#include <syslog.h>

#define String(str) Nan::New<v8::String>(str).ToLocalChecked()
#define Integer(str) Nan::New<v8::Integer>(str)
#define StringArg(arg) Nan::To<v8::String>(arg).ToLocalChecked()
#define IntegerArg(arg) Nan::To<int32_t>(arg).FromJust()
#define SET_CONST(name) Nan::Set(target, String(#name), Integer(LOG_##name));

// Syslog on Linux does not seem to copy the identity string itself to
// permanent storage.
char identity[256] = {0};

namespace Syslogh {
	NAN_METHOD(openlog) {
		// WriteUtf8 does not guarantee null-termination, so use a -1 length.
		Nan::Utf8String identityArg(StringArg(info[0]));
		strncat(identity, *identityArg, sizeof(identity)-1);
		int flags = IntegerArg(info[1]);
		int facility = IntegerArg(info[2]);
		::openlog(::identity, flags, facility);
	}

	NAN_METHOD(syslog) {
		int priority = IntegerArg(info[0]);
		Nan::Utf8String msg(StringArg(info[1]));
		::syslog(priority, "%s", *msg);
	}

	NAN_METHOD(closelog) {
		::closelog();
	}

	NAN_MODULE_INIT(initialize) {
		NAN_EXPORT(target, openlog);
		NAN_EXPORT(target, syslog);
		NAN_EXPORT(target, closelog);

		SET_CONST(CONS);
		SET_CONST(ODELAY);
		SET_CONST(PID);
		SET_CONST(NDELAY);
		SET_CONST(NOWAIT);

		// Seems available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_PERROR
		SET_CONST(PERROR);
		#endif

		SET_CONST(KERN);
		SET_CONST(USER);
		SET_CONST(MAIL);
		SET_CONST(DAEMON);
		SET_CONST(AUTH);
		SET_CONST(SYSLOG);
		SET_CONST(LPR);
		SET_CONST(NEWS);
		SET_CONST(UUCP);
		SET_CONST(CRON);

		// Available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_AUTHPRIV
		SET_CONST(AUTHPRIV);
		#endif

		SET_CONST(LOCAL0);
		SET_CONST(LOCAL1);
		SET_CONST(LOCAL2);
		SET_CONST(LOCAL3);
		SET_CONST(LOCAL4);
		SET_CONST(LOCAL5);
		SET_CONST(LOCAL6);
		SET_CONST(LOCAL7);

		SET_CONST(EMERG);
		SET_CONST(ALERT);
		SET_CONST(CRIT);
		SET_CONST(ERR);
		SET_CONST(WARNING);
		SET_CONST(NOTICE);
		SET_CONST(INFO);
		SET_CONST(DEBUG);
	}
}

NODE_MODULE(index, Syslogh::initialize);

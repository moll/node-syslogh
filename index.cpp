#include <node.h>
#include <v8.h>
#include <nan.h>
#include <syslog.h>

#define String(str) Nan::New<v8::String>(str).ToLocalChecked()
#define Integer(str) Nan::New<v8::Integer>(str)
#define StringArg(arg) Nan::To<v8::String>(arg).ToLocalChecked()
#define IntegerArg(arg) Nan::To<int32_t>(arg).FromJust()

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

		Nan::Set(target, String("CONS"), Integer(LOG_CONS));
		Nan::Set(target, String("ODELAY"), Integer(LOG_ODELAY));
		Nan::Set(target, String("PID"), Integer(LOG_PID));
		Nan::Set(target, String("NDELAY"), Integer(LOG_NDELAY));
		Nan::Set(target, String("NOWAIT"), Integer(LOG_NOWAIT));

		// Seems available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_PERROR
		Nan::Set(target, String("PERROR"), Integer(LOG_PERROR));
		#endif

		Nan::Set(target, String("KERN"), Integer(LOG_KERN));
		Nan::Set(target, String("USER"), Integer(LOG_USER));
		Nan::Set(target, String("MAIL"), Integer(LOG_MAIL));
		Nan::Set(target, String("DAEMON"), Integer(LOG_DAEMON));
		Nan::Set(target, String("AUTH"), Integer(LOG_AUTH));
		Nan::Set(target, String("SYSLOG"), Integer(LOG_SYSLOG));
		Nan::Set(target, String("LPR"), Integer(LOG_LPR));
		Nan::Set(target, String("NEWS"), Integer(LOG_NEWS));
		Nan::Set(target, String("UUCP"), Integer(LOG_UUCP));
		Nan::Set(target, String("CRON"), Integer(LOG_CRON));

		// Available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_AUTHPRIV
		Nan::Set(target, String("AUTHPRIV"), Integer(LOG_AUTHPRIV));
		#endif

		Nan::Set(target, String("LOCAL0"), Integer(LOG_LOCAL0));
		Nan::Set(target, String("LOCAL1"), Integer(LOG_LOCAL1));
		Nan::Set(target, String("LOCAL2"), Integer(LOG_LOCAL2));
		Nan::Set(target, String("LOCAL3"), Integer(LOG_LOCAL3));
		Nan::Set(target, String("LOCAL4"), Integer(LOG_LOCAL4));
		Nan::Set(target, String("LOCAL5"), Integer(LOG_LOCAL5));
		Nan::Set(target, String("LOCAL6"), Integer(LOG_LOCAL6));
		Nan::Set(target, String("LOCAL7"), Integer(LOG_LOCAL7));

		Nan::Set(target, String("EMERG"), Integer(LOG_EMERG));
		Nan::Set(target, String("ALERT"), Integer(LOG_ALERT));
		Nan::Set(target, String("CRIT"), Integer(LOG_CRIT));
		Nan::Set(target, String("ERR"), Integer(LOG_ERR));
		Nan::Set(target, String("WARNING"), Integer(LOG_WARNING));
		Nan::Set(target, String("NOTICE"), Integer(LOG_NOTICE));
		Nan::Set(target, String("INFO"), Integer(LOG_INFO));
		Nan::Set(target, String("DEBUG"), Integer(LOG_DEBUG));
	}
}

NODE_MODULE(index, Syslogh::initialize);

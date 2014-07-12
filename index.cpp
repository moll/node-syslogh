#include <node.h>
#include <v8.h>
#include <nan.h>
#include <syslog.h>

#define String(str) NanNew<v8::String>(str)
#define Integer(str) NanNew<v8::Integer>(str)

// Syslog on Linux does not seem to copy the identity string itself to
// permanent storage.
char identity[256] = {0};

namespace Syslogh {
	NAN_METHOD(openlog) {
		// WriteUtf8 does not guarantee null-termination, so use a -1 length.
		args[0]->ToString()->WriteUtf8(identity, sizeof(identity) - 1);
		int flags = args[1]->Int32Value();
		int facility = args[2]->Int32Value();
		::openlog(::identity, flags, facility);
		NanReturnUndefined();
	}

	NAN_METHOD(syslog) {
		int priority = args[0]->Int32Value();
		v8::String::Utf8Value msg(args[1]->ToString());
		::syslog(priority, "%s", *msg);
		NanReturnUndefined();
	}

	NAN_METHOD(closelog) {
		::closelog();
		NanReturnUndefined();
	}

	void initialize(v8::Handle<v8::Object> exports) {
		NODE_SET_METHOD(exports, "openlog", openlog);
		NODE_SET_METHOD(exports, "syslog", syslog);
		NODE_SET_METHOD(exports, "closelog", closelog);

		exports->Set(String("CONS"), Integer(LOG_CONS));
		exports->Set(String("ODELAY"), Integer(LOG_ODELAY));
		exports->Set(String("PID"), Integer(LOG_PID));
		exports->Set(String("NDELAY"), Integer(LOG_NDELAY));
		exports->Set(String("NOWAIT"), Integer(LOG_NOWAIT));

		// Seems available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_PERROR
		exports->Set(String("PERROR"), Integer(LOG_PERROR));
		#endif

		exports->Set(String("KERN"), Integer(LOG_KERN));
		exports->Set(String("USER"), Integer(LOG_USER));
		exports->Set(String("MAIL"), Integer(LOG_MAIL));
		exports->Set(String("DAEMON"), Integer(LOG_DAEMON));
		exports->Set(String("AUTH"), Integer(LOG_AUTH));
		exports->Set(String("SYSLOG"), Integer(LOG_SYSLOG));
		exports->Set(String("LPR"), Integer(LOG_LPR));
		exports->Set(String("NEWS"), Integer(LOG_NEWS));
		exports->Set(String("UUCP"), Integer(LOG_UUCP));
		exports->Set(String("CRON"), Integer(LOG_CRON));

		// Available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_AUTHPRIV
		exports->Set(String("AUTHPRIV"), Integer(LOG_AUTHPRIV));
		#endif

		exports->Set(String("LOCAL0"), Integer(LOG_LOCAL0));
		exports->Set(String("LOCAL1"), Integer(LOG_LOCAL1));
		exports->Set(String("LOCAL2"), Integer(LOG_LOCAL2));
		exports->Set(String("LOCAL3"), Integer(LOG_LOCAL3));
		exports->Set(String("LOCAL4"), Integer(LOG_LOCAL4));
		exports->Set(String("LOCAL5"), Integer(LOG_LOCAL5));
		exports->Set(String("LOCAL6"), Integer(LOG_LOCAL6));
		exports->Set(String("LOCAL7"), Integer(LOG_LOCAL7));

		exports->Set(String("EMERG"), Integer(LOG_EMERG));
		exports->Set(String("ALERT"), Integer(LOG_ALERT));
		exports->Set(String("CRIT"), Integer(LOG_CRIT));
		exports->Set(String("ERR"), Integer(LOG_ERR));
		exports->Set(String("WARNING"), Integer(LOG_WARNING));
		exports->Set(String("NOTICE"), Integer(LOG_NOTICE));
		exports->Set(String("INFO"), Integer(LOG_INFO));
		exports->Set(String("DEBUG"), Integer(LOG_DEBUG));
	}
}

NODE_MODULE(index, Syslogh::initialize);

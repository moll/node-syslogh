#include <node.h>
#include <v8.h>
#include <syslog.h>

// On Linux, FunctionCallbackInfo is already defined by something else other
// than V8's namespace. Use full name everywhere.
using v8::Handle;
using v8::Integer;
using v8::Object;
using v8::String;
using v8::Value;

namespace Syslogh {
	void openlog(const v8::FunctionCallbackInfo<Value>& args) {
		String::Utf8Value identity(args[0]->ToString());
		int flags = args[1]->Int32Value();
		int facility = args[2]->Int32Value();
		::openlog(*identity, flags, facility);
	}

	void syslog(const v8::FunctionCallbackInfo<Value>& args) {
		int priority = args[0]->Int32Value();
		String::Utf8Value msg(args[1]->ToString());
		::syslog(priority, "%s", *msg);
	}

	void closelog(const v8::FunctionCallbackInfo<Value>& args) {
		::closelog();
	}

	void initialize(Handle<Object> exports) {
		NODE_SET_METHOD(exports, "openlog", openlog);
		NODE_SET_METHOD(exports, "syslog", syslog);
		NODE_SET_METHOD(exports, "closelog", closelog);

		exports->Set(String::New("CONS"), Integer::New(LOG_CONS));
		exports->Set(String::New("ODELAY"), Integer::New(LOG_ODELAY));
		exports->Set(String::New("PID"), Integer::New(LOG_PID));
		exports->Set(String::New("NDELAY"), Integer::New(LOG_NDELAY));
		exports->Set(String::New("NOWAIT"), Integer::New(LOG_NOWAIT));

		// Seems available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_PERROR
		exports->Set(String::New("PERROR"), Integer::New(LOG_PERROR));
		#endif

		exports->Set(String::New("KERN"), Integer::New(LOG_KERN));
		exports->Set(String::New("USER"), Integer::New(LOG_USER));
		exports->Set(String::New("MAIL"), Integer::New(LOG_MAIL));
		exports->Set(String::New("DAEMON"), Integer::New(LOG_DAEMON));
		exports->Set(String::New("AUTH"), Integer::New(LOG_AUTH));
		exports->Set(String::New("SYSLOG"), Integer::New(LOG_SYSLOG));
		exports->Set(String::New("LPR"), Integer::New(LOG_LPR));
		exports->Set(String::New("NEWS"), Integer::New(LOG_NEWS));
		exports->Set(String::New("UUCP"), Integer::New(LOG_UUCP));
		exports->Set(String::New("CRON"), Integer::New(LOG_CRON));

		// Available on OS X but not in the UNIX syslog.h.
		#ifdef LOG_AUTHPRIV
		exports->Set(String::New("AUTHPRIV"), Integer::New(LOG_AUTHPRIV));
		#endif

		// Locals.
		exports->Set(String::New("LOCAL0"), Integer::New(LOG_LOCAL0));
		exports->Set(String::New("LOCAL1"), Integer::New(LOG_LOCAL1));
		exports->Set(String::New("LOCAL2"), Integer::New(LOG_LOCAL2));
		exports->Set(String::New("LOCAL3"), Integer::New(LOG_LOCAL3));
		exports->Set(String::New("LOCAL4"), Integer::New(LOG_LOCAL4));
		exports->Set(String::New("LOCAL5"), Integer::New(LOG_LOCAL5));
		exports->Set(String::New("LOCAL6"), Integer::New(LOG_LOCAL6));
		exports->Set(String::New("LOCAL7"), Integer::New(LOG_LOCAL7));

		exports->Set(String::New("EMERG"), Integer::New(LOG_EMERG));
		exports->Set(String::New("ALERT"), Integer::New(LOG_ALERT));
		exports->Set(String::New("CRIT"), Integer::New(LOG_CRIT));
		exports->Set(String::New("ERR"), Integer::New(LOG_ERR));
		exports->Set(String::New("WARNING"), Integer::New(LOG_WARNING));
		exports->Set(String::New("NOTICE"), Integer::New(LOG_NOTICE));
		exports->Set(String::New("INFO"), Integer::New(LOG_INFO));
		exports->Set(String::New("DEBUG"), Integer::New(LOG_DEBUG));
	}
}

NODE_MODULE(index, Syslogh::initialize);

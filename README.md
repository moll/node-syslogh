Syslogh.js
==========
[![NPM version][npm-badge]](http://badge.fury.io/js/syslogh)
[![Build status][travis-badge]](https://travis-ci.org/moll/node-syslogh)
[npm-badge]: https://badge.fury.io/js/syslogh.png
[travis-badge]: https://travis-ci.org/moll/node-syslogh.png?branch=master

Syslogh.js is a library for logging to your system's Syslog ([RFC
3164][rfc3164]) from within Node.js. It provides simple native bindings to
[`<syslog.h>`][syslog.h] and [`syslog(3)`][syslog(3)]. You're in luck, because
it does not come with any bells and whistles.  Intentionally. KISS, right?

Now works with both Node **v0.10** (stable) and **v0.11** (development).  
In fact, it's the only Syslog library I know that works with v0.11 as of today.

[rfc3164]: https://tools.ietf.org/html/rfc3164
[syslog.h]: http://pubs.opengroup.org/onlinepubs/7908799/xsh/syslog.h.html
[syslog(3)]: http://linux.die.net/man/3/syslog


Installing
----------
Install with: `npm install syslogh`


Using
-----
Using Syslogh.js is similar to using [`syslog(3)`][syslog(3)] from C/C++.  
First use `openlog` with **your app name** (up to 255 characters), [**options**](#options) and the
[**facility**](#facilities):
```javascript
var Syslogh = require("syslogh")
Syslogh.openlog("myapp", Syslogh.PID, Syslogh.LOCAL7)
```

Then, when logging, just pass in the [**severity**](#severities) and your
message.  
Just like with regular [`syslog(3)`][syslog(3)], you can use `sprintf` style
placeholders. Those internally use Node's built-in `Util.format`.
```javascript
Syslogh.syslog(Syslogh.NOTICE, "Freeze-frame high-five.")
Syslogh.syslog(Syslogh.NOTICE, "Phone %d.", 5)
```

You can also call `Syslogh.closelog` to close things down, but I'm not sure why
you should bother. :-) Exiting your Node.js program will most likely shut
everything down, too.

The [`syslog(3)`][syslog(3)] manpage also talks about `setlogmask` to filter
logs before they're sent. This isn't implemented. Not yet, at least.


### Options
Options to pass to `openlog` come from [`<syslog.h>`][syslog.h].

Option | Description
-------|------------
CONS   | Log to the system console on error.
ODELAY | Delay open until `syslog()` is called. (Often default.)
PID    | Log the process ID with each message.
NDELAY | Connect to syslog daemon immediately.
NOWAIT | Don't wait for child processes.

Access them as constants. E.g. `Syslogh.PID`.  
They form a bit mask, so to pass multiple of them to `openlog`, binary-OR them
together with the `|` operator:
```javascript
Syslogh.openlog("myapp", Syslogh.PID | Syslogh.NDELAY, Syslogh.LOCAL7)
```


### Facilities
Facilities to pass to `openlog` come from [`<syslog.h>`][syslog.h] and ([RFC
3164][rfc3164]).  
Some facilities might differ between systems. For your own app use, best stick
to `LOCAL*` facilities.

Facility | Description
---------|------------
KERN     | Kernel messages.
USER     | User-level messages.
MAIL     | Mail system.
DAEMON   | System daemons.
AUTH     | Security/authorization messages.
SYSLOG   | Messages generated internally by syslogd.
LPR      | Line printer subsystem.
NEWS     | Network news subsystem.
UUCP     | UUCP subsystem.
CRON     | Clock daemon.
AUTHPRIV | Security/authorization messages.
LOCAL0   | Local use 0.
LOCAL1   | Local use 1.
LOCAL2   | Local use 2.
LOCAL3   | Local use 3.
LOCAL4   | Local use 4.
LOCAL5   | Local use 5.
LOCAL6   | Local use 6.
LOCAL7   | Local use 7.

Access them as constants. E.g. `Syslogh.LOCAL7`.


### Severities
Severities to pass to `syslog` come from [`<syslog.h>`][syslog.h] and ([RFC
3164][rfc3164]).  

Severity | Description
---------|------------
EMERG    | System is unusable.
ALERT    | Action must be taken immediately.
CRIT     | Critical conditions.
ERR      | Error conditions.
WARNING  | Warning conditions.
NOTICE   | Normal but significant.
INFO     | Informational messages.
DEBUG    | Debug-level messages.

Access them as constants. E.g. `Syslogh.NOTICE`.


License
-------
Syslogh.js is released under a *Lesser GNU Affero General Public License*, which
in summary means:

- You **can** use this program for **no cost**.
- You **can** use this program for **both personal and commercial reasons**.
- You **do not have to share your own program's code** which uses this program.
- You **have to share modifications** (e.g. bug-fixes) you've made to this
  program.

For more convoluted language, see the `LICENSE` file.


About
-----
**[Andri Möll](http://themoll.com)** typed this and the code.  
[Monday Calendar](https://mondayapp.com) supported the engineering work.

If you find Syslogh.js needs improving, please don't hesitate to type to me now
at [andri@dot.ee][email] or [create an issue online][issues].

[email]: mailto:andri@dot.ee
[issues]: https://github.com/moll/node-syslogh/issues

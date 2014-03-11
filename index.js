var format = require("util").format
var slice = Array.prototype.slice
module.exports = exports = require("bindings")("index")

// Support printf-style strings like syslog(3) does.
var syslog_ = exports.syslog
exports.syslog = function syslog(type, msg) {
  if (arguments.length > 2) msg = format.apply(null, slice.call(arguments, 1))
  syslog_(type, msg)
}

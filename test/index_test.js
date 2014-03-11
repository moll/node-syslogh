var _ = require("underscore")
var Syslogh = require("..")

describe("Syslogh", function() {
  describe(".openlog", function() {
    it("must not throw", function() {
      var open = Syslogh.openlog.bind(null, "app", Syslogh.PID, Syslogh.LOCAL7)
      open.must.not.throw()
    })
  })

  describe(".syslog", function() {
    beforeEach(function() {
      Syslogh.openlog("Syslogh", Syslogh.PID, Syslogh.LOCAL0)
    })

    it("must not throw", function() {
      Syslogh.syslog.bind(null, Syslogh.DEBUG, "Test").must.not.throw()
    })

    it("must not throw when using sprintf placeholders", function() {
      Syslogh.syslog.bind(null, Syslogh.DEBUG, "%s %d %f").must.not.throw()
    })
  })

  describe(".closelog", function() {
    it("must not throw", function() {
      Syslogh.closelog.bind(null).must.not.throw()
    })
  })

  describe("flags", function() {
    _({
      PID: 0x01,
      CONS: 0x02,
      ODELAY: 0x04,
      NDELAY: 0x08,
      NOWAIT: 0x10
    }).each(function(value, name) {
      it("must have " + name + " equal to " + value, function() {
        Syslogh[name].must.equal(value)
      })
    })

    it("must have PERROR equal to 0x20 or not exist", function() {
      if (Syslogh.PERROR == null) return
      Syslogh.PERROR.must.equal(0x20)
    })
  })

  describe("facilities", function() {
    _({
      KERN: 0 << 3,
      USER: 1 << 3,
      MAIL: 2 << 3,
      DAEMON: 3 << 3,
      AUTH: 4 << 3,
      SYSLOG: 5 << 3,
      LPR: 6 << 3,
      NEWS: 7 << 3,
      UUCP: 8 << 3,
      CRON: 9 << 3,

      LOCAL0: 16 << 3,
      LOCAL1: 17 << 3,
      LOCAL2: 18 << 3,
      LOCAL3: 19 << 3,
      LOCAL4: 20 << 3,
      LOCAL5: 21 << 3,
      LOCAL6: 22 << 3,
      LOCAL7: 23 << 3,
    }).each(function(value, name) {
      it("must have " + name + " equal to " + value, function() {
        Syslogh[name].must.equal(value)
      })
    })

    it("must have AUTHPRIV equal to 10 << 3 or not exist", function() {
      if (Syslogh.AUTHPRIV == null) return
      Syslogh.AUTHPRIV.must.equal(10 << 3)
    })
  })

  describe("priorities", function() {
    _({
      EMERG: 0,
      ALERT: 1,
      CRIT: 2,
      ERR: 3,
      WARNING: 4,
      NOTICE: 5,
      INFO: 6,
      DEBUG: 7
    }).each(function(value, name) {
      it("must have " + name + " equal to " + value, function() {
        Syslogh[name].must.equal(value)
      })
    })
  })
})

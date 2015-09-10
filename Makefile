NODE = node
NODE_OPTS =
TEST_OPTS =
NODE_GYP = npm --ignore-scripts false run node-gyp

love:
	@echo "Feel like makin' love."

build: binding.gyp
	$(NODE_GYP) configure

compile: build
	$(MAKE) -C build

test: compile
	@$(NODE) $(NODE_OPTS) ./node_modules/.bin/_mocha -R dot $(TEST_OPTS)

spec:  compile
	@$(NODE) $(NODE_OPTS) ./node_modules/.bin/_mocha -R spec $(TEST_OPTS)

autotest: compile
	@$(NODE) $(NODE_OPTS) ./node_modules/.bin/_mocha -R dot --watch $(TEST_OPTS)

autospec: compile
	@$(NODE) $(NODE_OPTS) ./node_modules/.bin/_mocha -R spec --watch $(TEST_OPTS)

pack:
	npm pack

publish:
	npm publish

tag:
	git tag "v$$($(NODE) -e 'console.log(require("./package").version)')"

clean:
	rm -f *.tgz
	npm prune --production
	$(NODE_GYP) clean

.PHONY: love
.PHONY: compile
.PHONY: test spec autotest autospec
.PHONY: pack publish tag
.PHONY: clean

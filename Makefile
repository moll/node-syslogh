NODE_OPTS :=
TEST_OPTS :=

love:
	@echo "Feel like makin' love."

compile: build
	$(MAKE) -C build

build:
	node-gyp configure

test: compile
	@node $(NODE_OPTS) ./node_modules/.bin/_mocha -R dot $(TEST_OPTS)

spec:  compile
	@node $(NODE_OPTS) ./node_modules/.bin/_mocha -R spec $(TEST_OPTS)

autotest: compile
	@node $(NODE_OPTS) ./node_modules/.bin/_mocha -R dot --watch $(TEST_OPTS)

autospec: compile
	@node $(NODE_OPTS) ./node_modules/.bin/_mocha -R spec --watch $(TEST_OPTS)

pack:
	npm pack

publish:
	npm publish

tag:
	git tag "v$$(node -e 'console.log(require("./package").version)')"

clean:
	rm -f *.tgz
	npm prune --production
	node-gyp clean

.PHONY: love
.PHONY: compile
.PHONY: test spec autotest autospec
.PHONY: pack publish tag
.PHONY: clean

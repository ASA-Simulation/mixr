.PHONY: clean configure build install help

.DEFAULT_GOAL := help


# Custom variables
PWD := $(shell pwd)


configure: ## Configure the project for building.
	mkdir -p ./build/
	conan install ./ --build=missing --settings=build_type=Debug
	meson setup --reconfigure \
		--backend ninja \
		--buildtype debug \
		--prefix=$(PWD)/../out \
		-Dpkg_config_path=$(PWD)/../build:$(PWD)/build \
		./build/ .


build: ## Build all targets in the project.
	meson compile -C ./build


install: ## Install all targets in the project.
	meson install -C ./build


package: ## Package the project using conan.
	conan create ./ --build=missing --settings=compiler.cppstd=gnu11 --settings=build_type=Debug
	conan create ./ --build=missing --settings=compiler.cppstd=gnu11 --settings=build_type=Release


clean: ## Clean all generated build files in the project.
	rm -rf ./build/
	rm -rf ./subprojects/packagecache


help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

YAML_FILES = esphome-air-quality-monitor-*.yaml

.PHONY: build lint requirements

build:
	esphome compile $(YAML_FILES)

lint:
	yamllint .

requirements:
	pip3 install wheel
	pip3 install -r requirements.txt

BUILD_DIR = build
YAML_FILES = *_example.yaml

.PHONY: build clean lint requirements

build:
	esphome compile $(YAML_FILES)

clean:
	rm -r $(BUILD_DIR)

lint:
	yamllint .

requirements:
	pip3 install wheel
	pip3 install -r requirements.txt

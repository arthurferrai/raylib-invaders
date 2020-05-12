include common.mk

# C compiler
CC = clang
# C++ compiler
CXX = clang++
# extra c/c++ preprocessor and compiler flags
EXTRA_LDFLAGS += -framework OpenGL -framework OpenAL -framework Cocoa -framework CoreVideo -framework IOKit

BUNDLE_NAME = Raylib Invaders
BUNDLE_IDENTIFIER = br.nom.arthur.ferrai.invaders

.PHONY: app icns clean

all: app

app: $(BUILD_PATH)/$(PROJECT_NAME) $(BUILD_PATH)/Info.plist $(BUILD_PATH)/$(PROJECT_ICON).icns
	@echo -n 'Creating "$(BUILD_PATH)/$(BUNDLE_NAME).app"...'
	@$(MKDIR) "$(BUILD_PATH)/$(BUNDLE_NAME).app/Contents/MacOS"
	@$(MKDIR) "$(BUILD_PATH)/$(BUNDLE_NAME).app/Contents/Resources"
	@cp "$(BUILD_PATH)/$(PROJECT_ICON).icns" "$(BUILD_PATH)/$(BUNDLE_NAME).app/Contents/Resources/$(PROJECT_ICON).icns"
	@cp "$(BUILD_PATH)/Info.plist" "$(BUILD_PATH)/$(BUNDLE_NAME).app/Contents/Info.plist"
	@cp "$(BUILD_PATH)/$(PROJECT_NAME)" "$(BUILD_PATH)/$(BUNDLE_NAME).app/Contents/MacOS/$(PROJECT_NAME)"
	@echo Done.

ADD_STRING_VALUE = printf "\t<key>$(1)</key>\n\t<string>$(2)</string>\n" >> $@

$(BUILD_PATH)/Info.plist:
	@echo '<?xml version="1.0" encoding="UTF-8"?>' > $@
	@echo '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> $@
	@echo '<plist version="1.0">' >> $@
	@echo '<dict>' >> $@
	@$(call ADD_STRING_VALUE,CFBundleExecutable,$(PROJECT_NAME))
	@$(call ADD_STRING_VALUE,CFBundleName,$(BUNDLE_NAME))
	@$(call ADD_STRING_VALUE,CFBundleIdentifier,$(BUNDLE_IDENTIFIER))
	@$(call ADD_STRING_VALUE,CFBundleVersion,$(PROJECT_VERSION))
	@$(call ADD_STRING_VALUE,CFBundlePackageType,APPL)
	@$(call ADD_STRING_VALUE,CFBundleSignature,????)
	@$(call ADD_STRING_VALUE,CFBundleIconFile,$(PROJECT_ICON).icns)
	@echo '</dict>' >> $@
	@echo '</plist>' >> $@

ICON_SCALER = sips -z
ICNS_PACKER = iconutil -c icns

ICONSET = $(BUILD_PATH)/$(PROJECT_ICON).iconset

SILENT = &> /dev/null

$(BUILD_PATH)/$(PROJECT_ICON).icns: $(PROJECT_ICON).png
	@echo -n Generating icns file...
	@$(MKDIR) "$(ICONSET)"
	@$(ICON_SCALER) 1024 1024 "$<" --out "./$(ICONSET)/icon_512x512@2x.png" $(SILENT)

	@$(ICON_SCALER) 512 512 "$<" --out "./$(ICONSET)/icon_512x512.png" $(SILENT)
	@cp "./$(ICONSET)/icon_512x512.png" "./$(ICONSET)/icon_256x256@2x.png"

	@$(ICON_SCALER) 256 256 "$<" --out "./$(ICONSET)/icon_256x256.png" $(SILENT)
	@cp "./$(ICONSET)/icon_256x256.png" "./$(ICONSET)/icon_128x128@2x.png"

	@$(ICON_SCALER) 128 128 "$<" --out "./$(ICONSET)/icon_128x128.png" $(SILENT)
	@cp "./$(ICONSET)/icon_128x128.png" "./$(ICONSET)/icon_64x64@2x.png"

	@$(ICON_SCALER) 64 64 "$<" --out "./$(ICONSET)/icon_64x64.png" $(SILENT)
	@cp "./$(ICONSET)/icon_64x64.png" "./$(ICONSET)/icon_32x32@2x.png"

	@$(ICON_SCALER) 32 32 "$<" --out "./$(ICONSET)/icon_32x32.png" $(SILENT)
	@cp "./$(ICONSET)/icon_32x32.png" "./$(ICONSET)/icon_16x16@2x.png"

	@$(ICON_SCALER) 16 16 "$<" --out "./$(ICONSET)/icon_16x16.png" $(SILENT)

	@$(ICNS_PACKER) -o "./$@" "$(ICONSET)"

	@$(RM) "$(ICONSET)"
	@echo Done.

clean::
	@echo -n Removing app...
	@$(RM) "$(BUILD_PATH)/$(PROJECT_ICON).icns" $(BUILD_PATH)/Info.plist "$(BUILD_PATH)/$(BUNDLE_NAME).app"
	@echo Done.

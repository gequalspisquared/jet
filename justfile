# ===== Config =====

# Default build type
default_build := "debug"

# Directories
build_dir_debug := "build/debug"
build_dir_release := "build/release"

# Detect OS executable extension
exe_suffix := if os() == "windows" { ".exe" } else { "" }

# ===== Helpers =====

build-dir build_type:
    if [ "{{build_type}}" = "release" ]; then \
        echo {{build_dir_release}}; \
    else \
        echo {{build_dir_debug}}; \
    fi

cmake-build-type build_type:
    if [ "{{build_type}}" = "release" ]; then \
        echo Release; \
    else \
        echo Debug; \
    fi

# ===== Configure =====

configure build_type=default_build:
    @echo "Configuring {{build_type}} build..."
    mkdir -p `just build-dir {{build_type}}`
    cmake -S . -B `just build-dir {{build_type}}` \
        -DCMAKE_BUILD_TYPE=`just cmake-build-type {{build_type}}`

# ===== Build =====

build build_type=default_build: configure {{build_type}}
    @echo "Building {{build_type}}..."
    cmake --build `just build-dir {{build_type}}`

# ===== Run Tests =====

test build_type=default_build: build {{build_type}}
    @echo "Running tests ({{build_type}})..."
    cd `just build-dir {{build_type}}` && ctest --output-on-failure

# ===== Run Example =====

run build_type=default_build example="MinimalExample": build {{build_type}}
    @echo "Running example '{{example}}' ({{build_type}})..."
    `just build-dir {{build_type}}`/examples/{{example}}{{exe_suffix}}

# ===== Clean =====

clean:
    rm -rf build

# ===== Full Rebuild =====

rebuild build_type=default_build:
    rm -rf `just build-dir {{build_type}}`
    just build {{build_type}}

# ===== Convenience Targets =====

debug:
    just build debug

release:
    just build release

run-debug:
    just run debug

run-release:
    just run release

test-debug:
    just test debug

test-release:
    just test release

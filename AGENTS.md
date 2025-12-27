# Repository Guidelines

## Project Structure & Module Organization
- `src/` holds the C++ application sources and headers. Third-party code lives under `src/third_party/`.
- `cmake/` contains CMake helper modules and the CPack configuration template.
- `data/` includes runtime assets such as desktop files and other app resources.
- `images/` contains screenshots and artwork used in documentation.
- `CMakeLists.txt` is the build entry point.

## Build, Test, and Development Commands
- `cmake /path/to/radiotray-lite -DCMAKE_INSTALL_PREFIX=/usr` configures the project (run from a `build/` directory).
- `make -j$(nproc)` builds the binary after configuration.
- `cpack -G DEB` generates a Debian package under `build/packages/`.
- `cpack -G RPM` generates an RPM package under `build/packages/`.

Example:
```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
cpack -G DEB
```

## Coding Style & Naming Conventions
- C++ source uses 4-space indentation and brace-on-next-line for functions (follow existing style in `src/`).
- Keep file naming consistent with existing patterns (`*.cpp`, `*.hpp`).
- Prefer small, focused commits and avoid formatting-only changes unless needed.

## Testing Guidelines
- No automated test suite is defined in this repository.
- Validate changes by building the project and running the binary locally when possible.
- If you add tests, place them under a `tests/` directory and document how to run them.

## Commit & Pull Request Guidelines
- Commit messages are short and imperative; some use conventional prefixes like `fix:` or `chore:`. Either is acceptable as long as the intent is clear.
- PRs should include: a brief summary, build/package steps used, and any notable behavior changes. Include screenshots only if UI changes are visible.

## Configuration Notes
- Runtime configuration and bookmarks are stored under `$HOME/.config/radiotray-lite/`.
- If you introduce new config keys, update the README with examples.

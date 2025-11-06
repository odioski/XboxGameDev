# Contributing to Xbox Game Development Template

Thank you for your interest in contributing! This document provides guidelines for contributing to this project.

## Code of Conduct

- Be respectful and inclusive
- Provide constructive feedback
- Focus on what is best for the community
- Show empathy towards other community members

## How to Contribute

### Reporting Bugs

If you find a bug, please create an issue with:

1. **Clear title** describing the issue
2. **Detailed description** of the problem
3. **Steps to reproduce** the issue
4. **Expected behavior** vs actual behavior
5. **Environment details:**
   - Windows version
   - Visual Studio version
   - GDK version
   - Hardware specs (if relevant)
6. **Screenshots or error logs** if applicable

### Suggesting Features

We welcome feature suggestions! Please create an issue with:

1. **Clear description** of the feature
2. **Use case** - why is this feature needed?
3. **Proposed implementation** (if you have ideas)
4. **Alternatives considered**

### Pull Requests

1. **Fork the repository**
   ```bash
   git clone https://github.com/odioski/XboxGameDev.git
   cd XboxGameDev
   ```

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make your changes**
   - Follow the existing code style
   - Add comments where necessary
   - Update documentation if needed

4. **Test your changes**
   - Build the solution
   - Test on multiple configurations if possible
   - Verify no new warnings or errors

5. **Commit your changes**
   ```bash
   git add .
   git commit -m "Add feature: description of your changes"
   ```

6. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create Pull Request**
   - Go to the original repository
   - Click "New Pull Request"
   - Select your branch
   - Fill in the PR template

## Development Guidelines

### Code Style

- **C++ Standard:** C++17
- **Naming Conventions:**
  - Classes: PascalCase (e.g., `GameEngine`)
  - Functions: PascalCase (e.g., `Initialize()`)
  - Variables: camelCase (e.g., `frameCount`)
  - Member variables: m_ prefix (e.g., `m_deviceContext`)
  - Constants: c_ prefix (e.g., `c_maxBufferSize`)
- **Indentation:** 4 spaces (no tabs)
- **Braces:** Opening brace on same line for functions, new line for classes
- **Comments:** Use clear, concise comments where code intent isn't obvious

### Project Structure

```
XboxGameDev/
├── src/              # Implementation files (.cpp)
├── include/          # Header files (.h)
├── assets/           # Game assets
├── shaders/          # HLSL shaders
├── docs/             # Documentation
└── tests/            # Unit tests (if added)
```

### Documentation

- Update README.md if adding major features
- Update SETUP.md if changing build process
- Add comments to complex code sections
- Update TROUBLESHOOTING.md if solving common issues

### Testing

Before submitting a PR:

- [ ] Code builds without errors
- [ ] Code builds without warnings
- [ ] Tested on Debug configuration
- [ ] Tested on Release configuration
- [ ] No memory leaks (use appropriate tools)
- [ ] Documentation updated
- [ ] Code follows style guidelines

### Commit Messages

Write clear commit messages:

```
Add feature: Short description

Longer description if needed explaining what and why,
not how (the code shows how).

Fixes #123
```

## Areas Where We Need Help

- **Documentation improvements**
- **Example game implementations**
- **Additional shader examples**
- **Build system improvements**
- **Testing infrastructure**
- **Performance optimizations**
- **Bug fixes**

## Questions?

- Open an issue for questions about contributing
- Check existing issues and PRs first
- Be patient - maintainers are volunteers

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

## Recognition

Contributors will be recognized in the project README. Thank you for helping make this project better!

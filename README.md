[![✗](https://github.com/Alpha-Theta-Gamma-Mu/Flex-Bison-Compiler/actions/workflows/ci.yaml/badge.svg?branch=development)](https://github.com/Alpha-Theta-Gamma-Mu/Flex-Bison-Compiler/actions/workflows/ci.yaml)

# Flex-Bison-Compiler

A base compiler example, developed with Flex and Bison.

* [Requirements](#requirements)
* [Configuration](#configuration)
* [Commands](#commands)
* [CI/CD](#cicd)
* [Recommended Extensions](#recommended-extensions)

## Requirements

* [Docker v29.7.2](https://www.docker.com/)

## Configuration

Set the following environment variables to control and configure the behaviour of the application:

| Name                  | Default | Description                                                                                                                                                           |
| :-------------------- | :-----: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `ENVIRONMENT`         | `Local` | The active environment name. The available environments are: `Local`, `Development` and `Production`.                                                                 |
| `GDB_LISTENING_PORT`  | `2345`  | The host port where the GDB server is exposed.                                                                                                                        |
| `LOG_IGNORED_LEXEMES` | `true`  | When `true`, logs all of the ignored lexemes found with Flex at `DEBUGGING` level. To remove those logs from the console output, set it to `false`.                   |
| `LOGGING_LEVEL`       | `ALL`   | The minimum level to log in the console output. From lower to higher, the available levels are: `ALL`, `DEBUGGING`, `INFORMATION`, `WARNING`, `ERROR` and `CRITICAL`. |

_Docker Compose_ can read the variables from an `.env` file too (see `compose.yaml` file).

## Commands

### Start

Raises an ephemeral container, ready to start development:

```bash
docker compose run --rm compiler
```

### Build

Builds or rebuilds the entire compiler:

```bash
src/main/bash/build.sh
```

### Run

Compiles a program:

```bash
src/main/bash/run.sh <program>
```

where `<program>` is the path to the file that represents its entry point.

### Debug

The container exposes the _GDB_ server on the host port `GDB_LISTENING_PORT`. After building the compiler, run it through the _GDB_ server, which waits for an external debugger to connect:

```bash
docker compose run --rm --service-ports compiler
src/main/bash/build.sh
src/main/bash/debug.sh <program>
```

For example, you can connect to it from the host on port `2345` (the default) using:

```bash
gdb -ex "set substitute-path /home/ubuntu/Flex-Bison-Compiler $PWD" \
    -ex "target remote 127.0.0.1:2345" \
    -ex "break main" \
    .build/Flex-Bison-Compiler
```

### Test

Executes every available unit test under the `src/test/c` folder:

```bash
src/main/bash/test.sh
```

### Stop

Log out, destroy the ephemeral containers and shut down the cluster:

```bash
exit
docker compose down
```

### Docker

| Command                                 | Description                                             |
| :-------------------------------------- | :------------------------------------------------------ |
| `docker builder prune --all`            | Removes all builds and the complete build cache.        |
| `docker compose --progress=plain build` | Forces a build or rebuild of the images in the cluster. |
| `docker image prune`                    | Removes all of the dangling images from Docker.         |
| `docker network prune`                  | Removes unused networks from Docker.                    |
| `docker volume prune`                   | Removes unused volumes from Docker.                     |

## CI/CD

To trigger an automatic integration on every push or PR (_Pull Request_), you must activate _GitHub Actions_ in the _Settings_ tab. Use the following configuration:

| Key                                                        | Value                                               |
| :--------------------------------------------------------- | :-------------------------------------------------- |
| `Actions permissions`                                      | `Allow all actions and reusable workflows`          |
| `Allow GitHub Actions to create and approve pull requests` | `false`                                             |
| `Artifact and log retention`                               | `30 days`                                           |
| `Fork pull request workflows from outside collaborators`   | `Require approval for all outside collaborators`    |
| `Workflow permissions`                                     | `Read repository contents and packages permissions` |

## Recommended Extensions

* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
* [Yash](https://marketplace.visualstudio.com/items?itemName=daohong-emilio.yash)

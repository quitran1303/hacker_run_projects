## Project structure

There are three important directories: 

- `src` - source code
- `test` - test cases
- `test/unity` - unity test framework source

Test file names should start with `Test*` (case sensitive). Each test file should implement the `setUp`,  the`tearDown`, and the `main` functions since this project uses the default Unity test runner.

## How to run

You need to install `make`.

To run tests:

```bash
$ make test
```

To compile the code:

```bash
$ make compile
```

To generate an executable:

```bash
$ make install
```

To run all at once:

```bash
$ make
```

To clean:

```bash
$ make clean
```

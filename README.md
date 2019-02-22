# `openbsd-pledge`

> OpenBSD pledge(2) bindings for Node.js with prebuilds

## Usage

```js
const pledge = require('openbsd-pledge')
const fs = require('fs')

pledge('stdio')
const fd = fs.openSync('test.txt', 'r', 0o555) // SIGABRT here
```

## API

### `pledge([promise], [execpromise])`

`promise` and `execpromise` can be either space separated stringe of promises or
`null`. `promise` applies to the current process while `execpromise` applies to
child processes.

Please refer to the [`pledge(2)` docs](https://man.openbsd.org/pledge.2)

## Install

```sh
npm install openbsd-pledge
```

## License

[ISC](LICENSE)

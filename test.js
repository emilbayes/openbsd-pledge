var pledge = require('.')

pledge()
pledge(null)
pledge(null, null)
pledge(undefined, null)
pledge(null, 'stdio')
pledge('stdio')
pledge('stdio', null)
pledge('stdio', 'stdio')
pledge('', '')
process.stdout.write('')

{
  "targets": [{
    "target_name": "openbsd_pledge",
    "include_dirs": [
      "<!(node -e \"require('napi-macros')\")"
    ],
    'cflags':[
      '-pedantic-errors',
      '-Wall',
      '-std=gnu99',
    ],
    "sources": [ "./binding.c" ]
  }]
}

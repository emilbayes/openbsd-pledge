{
  "targets": [{
    "target_name": "openbsd_pledge",
    "include_dirs": [
      "<!(node -e \"require('napi-macros')\")"
    ],
    "sources": [ "./binding.c" ]
  }]
}

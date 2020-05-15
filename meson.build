project('caminhad', 'c', license: 'GPL-3', version: '0.1.0')

deps = dependency('libsystemd')

sources = files([
  'src/freedesktop_notification.c',
  'src/freedesktop_notification_messages.c',
  'main.c'
])

executable(meson.project_name(), sources, dependencies: deps)


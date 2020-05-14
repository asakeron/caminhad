project ('caminhad', 'c')

deps = dependency ('libsystemd')

sources = [
  'src/freedesktop_notification.c',
  'src/freedesktop_notification_messages.c',
  'main.c'
]

executable ('caminhad', sources, dependencies: deps)

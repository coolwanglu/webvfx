{
  'targets': [
    {
      'target_name': 'mltchromix',
      'type': 'shared_library',
      'variables': {
        'chromium_code': 1,
      },
      'dependencies': [
        'chromix.gyp:chromix',
      ],
      'conditions': [
        ['OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris"', {
          'cflags': [
            '<!@(pkg-config --cflags mlt-framework)',
          ],
          'link_settings': {
            'ldflags': [
              '<!@(pkg-config --libs-only-L --libs-only-other mlt-framework)',
            ],
            'libraries': [
              '<!@(pkg-config --libs-only-l mlt-framework)',
            ],
          },
        }], # OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris"
        ['OS=="mac"', {
          'xcode_settings': {
            'OTHER_CFLAGS': [
              '<!@(pkg-config --cflags mlt-framework)',
            ],
            'OTHER_LDFLAGS': [
              '<!@(pkg-config --libs mlt-framework)',
            ],
          },
        }], # OS=="mac"
      ],
      'sources': [
        'mlt/factory.c',
        'mlt/chromix_helper.h',
        'mlt/chromix_helper.cc',
        #XXX'mlt/filter_chromix.c',
      ],
    },
  ]
}

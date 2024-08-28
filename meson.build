project('DotDash', 'c',
        default_options: ['warning_level=2', 'c_std=c11'])

gtk_dep = dependency('gtk4')

src_dir = 'source'
inc_dir = 'include'

executable('app',
        sources: ['main.c', 
                  src_dir / 'alphabet.c', 
                  src_dir / 'activation.c',
                  src_dir / 'callbacks.c'],
        include_directories: inc_dir,
        dependencies: gtk_dep,
        install: true
)

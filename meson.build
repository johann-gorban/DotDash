project('Telegraf', 'c',
        default_options: ['warning_level=2', 'c_std=c11'])

gtk_dep = dependency('gtk4')

src_dir = 'source'
inc_dir = 'include'

executable('app',
        sources: [src_dir / 'main.c', src_dir / 'telegraf-alphabet.c', src_dir / 'telegraf-init.c'],
        include_directories: inc_dir,
        dependencies: gtk_dep,
        install: true
)

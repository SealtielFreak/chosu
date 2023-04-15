require_relative 'lib/chosu/version'

Gem::Specification.new do |s|
    s.name        = 'chosu'
    s.version     = Chosu::VERSION
    s.summary     = 'Simple game library for Ruby'
    s.description = 'Chopo is a framework for game develop, power by SFML'
    s.homepage    = 'https://github.com/sealtielfreak/chosu/'
    
    s.authors     = ['Sealtiel Valderrama']
    s.email       = 'SealtielFreak@yandex.com'
    s.license     = 'GPL-3.0'

    s.required_ruby_version = '>= 3.0'
    s.platform = Gem::Platform::RUBY

    s.add_development_dependency 'rake', '~> 11.2', '>= 11.2.2'

    s.files       = Dir.glob('ext/**/*.{rb,sh}') +
                    Dir.glob('ext/include/**/*.{h}') +
                    Dir.glob('ext/src/*.{c}') +

                    Dir.glob('lib/**/*.{rb}') +
                    Dir.glob('bin/**/*.{rb}') +
                    Dir.glob('test/**/*.{rb,png,otf}') +

                    Dir.glob('assets/**/*.{otf}')

    s.extensions  = ['ext/extconf.rb']
end

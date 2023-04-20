require 'mkmf'
require 'rake'
require_relative 'lib/chosu/version'

task default: 'all'

task :uninstall do
  system "gem uninstall chosu"
end

task :build do
  system "gem build chosu"
end

task :install do
  system "gem install chosu-#{Chosu::VERSION}.gem"
end

task :test do
  # nothing
end

task :all do
  Rake::Task['uninstall'].invoke
  Rake::Task['build'].invoke
  Rake::Task['install'].invoke
end

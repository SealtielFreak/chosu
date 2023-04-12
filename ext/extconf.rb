require 'mkmf'
require_relative 'auxlib.rb'

$INCFLAGS << " -Iinclude/"

if System.windows?
  run_script 'msys2.sh'
else
  run_script 'linux.sh'
end

%w[
  csfml-graphics csfml-audio csfml-network csfml-window csfml-system
].each { |l| abort unless have_library(l) }

create_makefile 'extchosu', 'src'
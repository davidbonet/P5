# Programas del proyecto

sources = [
	'instruments/instrument.cpp',
	'instruments/instrument_dumb.cpp',
	'instruments/seno.cpp',
	'instruments/tablaext.cpp',
	'instruments/samplers.cpp',
	'instruments/vibratoFM.cpp',
	'synth/envelope_adsr.cpp',
	'synth/midi_score.cpp',
	'synth/multinote_instr.cpp',
	'synth/orchest.cpp',
	'synth/synthesizer.cpp',
	'effects/effect.cpp',
	'effects/tremolo.cpp',
	'effects/vibrato.cpp',
	'effects/distortion.cpp',
	'effects/chorus.cpp',
]

executable(
    'synth',
    sources: sources,
    include_directories: inc,
    link_args: ['-lm', '-lsndfile'],
    link_with: lib_pav,
    install: true,
)

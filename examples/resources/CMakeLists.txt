
set(RESOURCE_FILES
	instances.frag
	instances.vert
	mrt_persp.frag
	mrt_persp.vert
	mrt_triangle.frag
	mrt_triangle.vert
	triangle.frag
	triangle.vert
)

set(RESOURCE_EFFECTS_FILES
	effects/wave.vert
	effects/skybox.vert
	effects/skybox.frag
	effects/reflection.vert
	effects/reflection.frag
	effects/position.vert
	effects/phong.vert
	effects/phong.hsh
	effects/phong.frag
	effects/normals.vert
	effects/normals.frag
	effects/noise.vert
	effects/main.vert
	effects/main.frag
	effects/interleave.frag
	effects/debug.vert
	effects/debug_normals.frag
	effects/debug.frag
	effects/dark.frag
	effects/bump.vert
	effects/bump.frag
	effects/blend_texture2d.vert
	effects/blend_texture2d.frag
)

set(RESOURCE_MODELS_FILES
	models/wall_normals.jpg
	models/rooftiles_normals.jpg
	models/rooftiles_bumpmap.jpg
	models/monkey.png
	models/monkey.ply
	models/monkey_painted.dae
	models/monkey_low.ply
	models/monkey_high.ply
	models/enviroment_storm.jpg
	models/enviroment_space.jpg
	models/enviroment_sea.jpg
	models/enviroment_rubic.png
	models/enviroment_restaurant.jpg
	models/enviroment_debug.jpg
)

set (RESOURCES_INSTALL_DIR share/glpp/examples)

install( FILES ${RESOURCE_FILES}
	DESTINATION ${RESOURCES_INSTALL_DIR}
	)
	
install( FILES ${RESOURCE_MODELS_FILES}
	DESTINATION ${RESOURCES_INSTALL_DIR}/models
	)
	
install( FILES ${RESOURCE_EFFECTS_FILES}
	DESTINATION ${RESOURCES_INSTALL_DIR}/effects
	)
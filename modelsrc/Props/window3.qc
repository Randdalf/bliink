$modelname	"props\window3.mdl"
$cdmaterials	"models\props\"
$scale 60

$body mybody	"RigidBodyWorld.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"RigidBodyWorld.smd"

$collisionmodel	"RigidBodyWorld.smd" { $concave }
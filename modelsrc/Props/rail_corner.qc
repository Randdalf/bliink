$modelname	"props\rail_corner.mdl"
$cdmaterials	"models\props\"
$scale 20

$body mybody	"rail_corner.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"rail_corner.smd"

$collisionmodel	"rail_corner.smd" { $concave }
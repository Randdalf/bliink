$modelname	"props\rail_cross.mdl"
$cdmaterials	"models\props\"
$scale 20

$body mybody	"rail_cross.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"rail_cross.smd"

$collisionmodel	"rail_cross.smd" { $concave }
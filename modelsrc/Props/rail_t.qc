$modelname	"props\rail_t.mdl"
$cdmaterials	"models\props\"
$scale 20

$body mybody	"rail_t.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"rail_t.smd"

$collisionmodel	"rail_t.smd" { $concave }
//'use strict';
console.log('+____________+');
const buildType = process.config.target_defaults.default_configuration;
const nodeMajorVersion = process.versions.node.split('.')[0];
const nodeMinorVersion = process.versions.node.split('.')[1];
const child_process = require('child_process');                       

function checkNodeVersion() {
  if (nodeMajorVersion >= 10 && nodeMinorVersion >= 2)
    return true;
  else
    return false;
}


if (process.argv[2] === 'child') {                                    
  console.log('child..........');
}

test(require(`./build/${buildType}/binding.node`), '1');
test(require(`./build/${buildType}/binding_noexcept.node`), '2');

function test(binding, name) {
  if (!checkNodeVersion())
    return;
  console.log(name);
  console.log(process.execPath);
  console.log(__filename);
  //const { stdout } =
          child_process.spawnSync(process.execPath, [__filename, 'child']);
  //binding.cleanup.doCleanup();
  /*
  const common = require('../../common');
  const assert = require('assert');                                
                                                                        
  if (process.argv[2] === 'child') {                                    
	    require(`./build/${common.buildType}/binding`);                     
  } else {                                                              
	    const { stdout } =                                                  
			    child_process.spawnSync(process.execPath, [__filename, 'child']); 
		  assert.strictEqual(stdout.toString().trim(), 'cleanup(42)');        
  }                                                                     
  */
}

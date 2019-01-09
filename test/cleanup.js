'use strict';
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

test(require(`./build/${buildType}/binding.node`));
test(require(`./build/${buildType}/binding_noexcept.node`));

function test(binding) {
  if (!checkNodeVersion())
    return;
  binding.cleanup.doCleanup();
  const common = require('../../common');
  const assert = require('assert');                                     
                                                                        
  if (process.argv[2] === 'child') {                                    
	    require(`./build/${common.buildType}/binding`);                     
  } else {                                                              
	    const { stdout } =                                                  
			    child_process.spawnSync(process.execPath, [__filename, 'child']); 
		  assert.strictEqual(stdout.toString().trim(), 'cleanup(42)');        
  }                                                                     

}

'use strict';
const buildType = process.config.target_defaults.default_configuration;
const nodeMajorVersion = process.versions.node.split('.')[0];
const nodeMinorVersion = process.versions.node.split('.')[1];

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
  binding.cleanup.addCleanupHookWithNullArg();
  binding.cleanup.removeCleanupHookWithNullArg();
  binding.cleanup.addCleanupHook();
}

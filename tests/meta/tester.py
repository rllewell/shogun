import glob
from optparse import OptionParser
import os
import sys

from modshogun import SerializableAsciiFile, WrappedObjectArray


if __name__ == "__main__":
    op = OptionParser()
    op.add_option("-t", "--target", action="store",
                  help="Target language directory")
    op.add_option("-r", "--rel_dir", action="store",
                  help="Relative directory of test")
    op.add_option("-f", "--file", action="store",
                  help="Test reference file")
    op.add_option("-g", "--generated_dir", action="store",
                  help="Directory of generated result file")
    op.add_option("-i", "--reference_dir", action="store",
                  help="Directory of reference result file")
    
    opts, args = op.parse_args()
    rel_dir = opts.rel_dir
    fname = opts.file
    target = opts.target
    
    generated_dir = opts.generated_dir
    reference_dir = opts.reference_dir
    
    fname_full_generated = os.path.join(generated_dir, target, rel_dir, fname)
    fname_full_reference = os.path.join(reference_dir, rel_dir, fname)
    
    # make sure files exist
    with open(fname_full_generated, 'r') as f:
        pass
    with open(fname_full_reference, 'r') as f:
        pass
    
    f = SerializableAsciiFile(fname_full_generated)
    f_ref = SerializableAsciiFile(fname_full_reference)
    
    a = WrappedObjectArray()
    a_ref = WrappedObjectArray()
    
    a.load_serializable(f)
    a_ref.load_serializable(f_ref)
    
    equal = a.equals(a_ref)
    
    if not equal:
        s = "mismatches reference file"
    else:
        s = "matches reference file"
    
    print("Generated %s %s." % (os.path.join(target, rel_dir, fname), s))
    
    if not equal:
        print("Options: %s" % str(opts))
        
    assert(equal)


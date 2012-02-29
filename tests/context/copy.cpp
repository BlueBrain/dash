
/* Copyright (c) 2011, EFPL/Blue Brain Project
 *                     Stefan Eilemann <stefan.eilemann@epfl.ch> 
 *
 * This file is part of DASH <https://github.com/BlueBrain/dash>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//#define DASH_TEST_NO_WATCHDOG
#include "test.h"
#include <dash/Attribute.h>
#include <dash/Context.h>
#include <dash/Node.h>

#include <dash/detail/Attribute.h>
#include <dash/detail/Change.h>
#include <dash/detail/Commit.h>
#include <dash/detail/Context.h>
#include <dash/detail/Node.h>

int dash::test::main( int argc, char **argv )
{
    dash::Context& mainCtx = dash::Context::getMain( argc, argv );
    dash::NodePtr node = new dash::Node;
    TEST( node->getRefCount() == 1 );

    dash::AttributePtr attribute = new dash::Attribute;
    TEST( attribute->getRefCount() == 1 );

    dash::detail::NodePtr iNode = node->getImpl();
    dash::detail::AttributePtr iAttribute = attribute->getImpl();
    node = 0;
    attribute = 0;

    TEST( iNode->getRefCount() == 1 );
    TEST( iAttribute->getRefCount() == 1 );
    iNode = 0;
    iAttribute = 0;

    node = new dash::Node;
    TEST( node->getRefCount() == 1 );

    attribute = new dash::Attribute;
    TEST( attribute->getRefCount() == 1 );

    dash::NodePtr mainChild = new dash::Node;
    node->insert( mainChild );
    TEST( node->getNChildren() == 1 );
    TESTINFO( node->getRefCount() == 1, node->getRefCount( ));  
    TESTINFO( mainChild->getRefCount() == 2, mainChild->getRefCount( ));
    TESTINFO( mainChild->getNParents() == 1, mainChild->getNParents( ));
    TESTINFO( mainCtx.getImpl().commit_->getImpl()->changes_->empty( ),
              *(mainCtx.getImpl().commit_->getImpl()->changes_) );

    {
        dash::Context auxCtx;
        TEST( auxCtx.getImpl().getSlot() == 1 );
        TESTINFO( mainCtx.getImpl().commit_->getImpl()->changes_->empty( ),
                  *(mainCtx.getImpl().commit_->getImpl()->changes_) );

        mainCtx.map( node, auxCtx );
        auxCtx.apply( mainCtx.commit( ));
        TESTINFO( mainCtx.getImpl().commit_->getImpl()->changes_->empty( ),
                  *(mainCtx.getImpl().commit_->getImpl()->changes_) );

        auxCtx.setCurrent();
        TEST( &dash::Context::getCurrent() == &auxCtx );
        TEST( node->getNChildren() == 1 );
        TESTINFO( mainCtx.getImpl().commit_->getImpl()->changes_->empty( ),
                  *(mainCtx.getImpl().commit_->getImpl()->changes_) );

        dash::NodePtr copyChild = new dash::Node;
        node->insert( copyChild );

        TEST( node->getNChildren() == 2 );
        TESTINFO( node->getRefCount() == 1, node->getRefCount( ));
        // variable, parent, change, change ContextDeleter
        TESTINFO( copyChild->getRefCount() == 4, copyChild->getRefCount( ));
        TESTINFO( copyChild->getNParents() == 1, copyChild->getNParents( ));
        TESTINFO( mainCtx.getImpl().commit_->getImpl()->changes_->empty( ),
                  *(mainCtx.getImpl().commit_->getImpl()->changes_) );

        {
            const dash::Commit commit = auxCtx.commit();
            dash::detail::ChangesPtr changes = commit.getImpl()->changes_;
            TESTINFO( mainCtx.getImpl().commit_->getImpl()->changes_->empty( ),
                      *(mainCtx.getImpl().commit_->getImpl()->changes_) );
            TESTINFO( changes->size() == 1, *changes );
            TESTINFO( node->getRefCount() == 1, node->getRefCount( ));

            mainCtx.apply( commit );
            changes = mainCtx.getImpl().commit_->getImpl()->changes_;
            TESTINFO( changes->size() == 1, *changes );

            mainCtx.setCurrent();
            TESTINFO( copyChild->getNParents() == 1, copyChild->getNParents( ));
            auxCtx.setCurrent();
        }
        TESTINFO( node->getRefCount() == 1, node->getRefCount( ));

        // variable, auxCtx Change + ContextDeleter, two context child vectors
        TESTINFO( copyChild->getRefCount() == 5, copyChild->getRefCount( ));
        TESTINFO( copyChild->getNParents() == 1, copyChild->getNParents( ));

        auxCtx.unmap( node );
        mainCtx.setCurrent();
        TESTINFO( node->getNChildren() == 2, node->getNChildren( ));
        TESTINFO( node->getRefCount() == 1, node->getRefCount( ));
        TESTINFO( copyChild->getNParents() == 1, copyChild->getNParents( ));

        node->erase( mainChild );
        TESTINFO( mainChild->getRefCount() == 2, mainChild->getRefCount( ));
        TESTINFO( copyChild->getNParents() == 1, copyChild->getNParents( ));

        {
            const dash::Commit commit = mainCtx.commit();
            dash::detail::ChangesPtr changes = commit.getImpl()->changes_;
            TESTINFO( changes->size() == 2, *changes );
        }
        TESTINFO( mainChild->getRefCount() == 1, mainChild->getRefCount( ));
        TESTINFO( copyChild->getNParents() == 1, copyChild->getNParents( ));

        TESTINFO( node->getRefCount() == 1, node->getRefCount( ));
        TESTINFO( node->getNChildren() == 1, node->getNChildren( ));
        TESTINFO( copyChild->getRefCount() == 2, copyChild->getRefCount( ));

        dash::detail::ChangesPtr changes = 
            mainCtx.getImpl().commit_->getImpl()->changes_;
        TESTINFO( changes->size() == 0, *changes );
    }

    dash::detail::ChangesPtr changes =
        mainCtx.getImpl().commit_->getImpl()->changes_;
    TESTINFO( changes->size() == 0, *changes );
    {
        dash::Context auxCtx;
        TEST( auxCtx.getImpl().getSlot() == 1 );
    }

    TESTINFO( node->getNChildren() == 1, node->getNChildren( ));

    dash::NodePtr child = *node->childrenBegin();
    TEST( child != mainChild );
    TESTINFO( child->getRefCount() == 2, child->getRefCount( ));
    TESTINFO( node->getRefCount() == 1, node->getRefCount( ));
    TESTINFO( child->getNParents() == 1, child->getNParents( ));

    iNode = node->getImpl();
    node = 0;
    mainCtx.commit();

    TEST( iNode->getRefCount() == 1 );
    iNode = 0;

    TESTINFO( child->getRefCount() == 1, child->getRefCount( ));
    TEST( !child->hasParents( ));
    child = 0;

    mainCtx.commit();
    delete &mainCtx;
    return EXIT_SUCCESS;
}

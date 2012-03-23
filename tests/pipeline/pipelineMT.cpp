
/* Copyright (c) 2011-2012, EFPL/Blue Brain Project
 *                     Ahmet Bilgili
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

#include "test.h"

#include <dash/Context.h>
#include <dash/Attribute.h>

#include <lunchbox/thread.h>
#include <lunchbox/mtQueue.h>

#define MAX_QUEUE_SIZE  5
#define MULT_CONST      2
#define ITERATION_COUNT 50
#define FILTER_COUNT    10
#define ATTR_INIT_VALUE 20
#define PROD_BEGIN_VAL  1

typedef lunchbox::MTQueue<dash::Commit, MAX_QUEUE_SIZE> CommitQueue;

class Producer : public lunchbox::Thread
{
public:
    Producer(CommitQueue* output)
        :outputQ_(output)
    {
        context_.setCurrent();
        attr_ = new dash::Attribute(ATTR_INIT_VALUE);
    }

    virtual ~Producer() {}

    virtual void run()
    {
        int producedData = PROD_BEGIN_VAL;
        context_.setCurrent();

        while( true )
        {
            ++producedData;
            if( producedData == ITERATION_COUNT )
                producedData = 0;
            *attr_ = producedData;
            lunchbox::sleep( producedData );
            const int attrProducedData =
                    static_cast< dash::AttributeConstPtr >( attr_ )->get<int>();
            TESTINFO(attrProducedData == producedData,
                     producedData << "!=" << attrProducedData );
            dash::Commit commit = context_.commit();
            outputQ_->push(commit);
            if( producedData == 0 )
                exit();
        }
    }

    dash::AttributePtr mapAttributeToContext(dash::Context& toContext)
    {
        context_.map(attr_, toContext);
        return attr_;
    };

private:
    dash::Context context_;
    CommitQueue* outputQ_;
    dash::AttributePtr attr_;
};

class Filter: public lunchbox::Thread
{
public:
    Filter()
        :inputQ_(NULL), outputQ_(NULL), filterNo_(++sFilterNo_),
         consumeMultiplier_(1)
    {
        for(int i = 0; i < filterNo_ - 1; ++i)
            consumeMultiplier_ *= MULT_CONST;
    }

    void setInputQueue(CommitQueue* input) { inputQ_ = input; }
    void setOutputQueue(CommitQueue* output) { outputQ_ = output; }

    virtual ~Filter()
    {
        context_.setCurrent();
        context_.commit();  // consume remaining changes
    }

    virtual void run()
    {
        int producerData = PROD_BEGIN_VAL;
        context_.setCurrent();

        while( true )
        {
            ++producerData;
            if( producerData == ITERATION_COUNT )
                producerData = 0;
            lunchbox::sleep( filterNo_ );
            dash::Commit commit = inputQ_->pop();
            context_.apply(commit);
            const int outData =
                    static_cast< dash::AttributeConstPtr >( attr_ )->get<int>();
            TESTINFO( outData == consumeMultiplier_ * producerData,
                      outData << "!=" << consumeMultiplier_ * producerData );
            *attr_ = MULT_CONST * outData;
            commit = context_.commit();
            outputQ_->push(commit);
            if(outData == 0)
                exit();
        }
    }

    void setAttribute(const dash::AttributePtr attr) { attr_ = attr; }
    dash::Context& getContext() { return context_; }

    dash::AttributePtr mapAttributeToContext(dash::Context& toContext)
    {
        context_.map(attr_, toContext);
        return attr_;
    };

private:

    static int sFilterNo_;
    dash::Context context_;
    CommitQueue* inputQ_;
    CommitQueue* outputQ_;
    dash::AttributePtr attr_;
    int filterNo_;
    int consumeMultiplier_;
};

int Filter::sFilterNo_ = 0;

class Consumer : public lunchbox::Thread
{
public:
    Consumer(CommitQueue* input)
    : inputQ_(input), consumeMultiplier_(1)
    {
        for(int i = 0; i < FILTER_COUNT; ++i)
            consumeMultiplier_ *= MULT_CONST;
    }

    virtual ~Consumer()
    {
        context_.setCurrent();
        context_.commit();  // consume remaining changes
    }

    virtual void run()
    {
        int producerData = PROD_BEGIN_VAL;
        context_.setCurrent();
        while( true )
        {
            ++producerData;
            if( producerData == ITERATION_COUNT )
                producerData = 0;
            const int targetConsumedData = producerData * consumeMultiplier_;
            dash::Commit iCommit = inputQ_->pop();
            context_.apply(iCommit);
            const int consumedData =
                    static_cast< dash::AttributeConstPtr >( attr_ )->get<int>();
            TESTINFO(consumedData == targetConsumedData,
                     consumedData << "!=" << targetConsumedData);
            if(consumedData == 0)
                exit();
        }
    }

    void setAttribute(const dash::AttributePtr attr) { attr_ = attr; }
    dash::Context& getContext() { return context_; }

private:

    dash::Context context_;
    CommitQueue* inputQ_;
    dash::AttributePtr attr_;
    int consumeMultiplier_;
};

int dash::test::main( int argc, char **argv )
{
    dash::Context& mainCtx = dash::Context::getMain( argc, argv );
    {
        CommitQueue queue[ FILTER_COUNT + 1 ];

        Filter filter[ FILTER_COUNT ];

        Producer producer( &queue[0] );
        for(int i = 0; i < FILTER_COUNT; ++i)
        {
            filter[ i ].setInputQueue( &queue[ i ] );
            filter[ i ].setOutputQueue( &queue[ i + 1 ] );
        }
        Consumer consumer( &queue[ FILTER_COUNT ] );

        filter[0].setAttribute( producer.mapAttributeToContext( filter[ 0 ].getContext() ) );
        for(int i = 1; i < FILTER_COUNT; ++i)
            filter[ i ].setAttribute( filter[ i - 1 ].mapAttributeToContext( filter[ i ].getContext() ) );
        consumer.setAttribute( filter[ FILTER_COUNT - 1 ].mapAttributeToContext( consumer.getContext() ) );

        producer.start();
        for(int i = 0; i < FILTER_COUNT; ++i)
            filter[ i ].start();
        consumer.start();

        producer.join();
        for(int i = 0; i < FILTER_COUNT; ++i)
                filter[ i ].join();
        consumer.join();
    }

    mainCtx.commit();
    delete &mainCtx;

    return EXIT_SUCCESS;
}
